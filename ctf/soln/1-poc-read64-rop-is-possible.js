// Disable ASLR:
// setarch `uname -m` -R /bin/bash
// Dump stuff:
// python3 Tools/Scripts/dump-class-layout -t WebKitBuild/JSCOnly/Debug/lib/libJavaScriptCore.so JavaScriptCore JSC::JITCode

const verbose = true
let output = true

// -------------------------------------------------------------------------

function addrOf(o, doOutput = true) {
    return $vm.addrOf(o, verbose && output && doOutput)
}

function fakeObj(o) {
    return $vm.fakeObj(o, verbose && output)
}

function read64(addr) {
    return $vm.read64(addr, verbose && output)
}

function write64(addr, val) {
    return $vm.write64(addr, val, verbose && output)
}

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

if (verbose)
    $vm.dumpRegisters()

let stack = deref(globalThis, "JSGlobalProxy::m_target.JSGlobalObject::m_vm.VM::topEntryFrame")
p("A stack address:")
hd(stack)

p("---")

function findReturnAddress(a, b, c, d, e, f, g, h, i, j, k, l) {
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

    //$vm.crash()

    p("Found non-cloop ret pc at:") // I searched in GDB for this offset
    let retPC = myStack - 0xb31fff30n + 0xbfffedacn
    hd(retPC)

    let retPCVal = read64(retPC)

    hd(retPCVal & 0xFFFFFFFFn)
    retPCVal = (retPCVal & (~0xFFFFFFFFn)) | 0xBFBF691137n

    write64(retPC, retPCVal)
    p('Written!')
}

findReturnAddress(0xBF, 0xEF)

