// Disable ASLR:
// setarch `uname -m` -R /bin/bash
// Dump stuff:
// python3 Tools/Scripts/dump-class-layout -t WebKitBuild/JSCOnly/Debug/lib/libJavaScriptCore.so JavaScriptCore JSC::JITCode

const verbose = false

// -------------------------------------------------------------------------

function addrOf(o) {
    return $vm.addrOf(o, verbose)
}

function fakeObj(o) {
    return $vm.fakeObj(o, verbose)
}

function read64(addr) {
    return $vm.read64(addr, verbose)
}

function write64(addr, val) {
    return $vm.write64(addr, val, verbose)
}

// -------------------------------------------------------------------------

const verboseDeref = true
let output = true

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
    // If you decide to use jit, enable this.
    // for (let i = 0; i < 1000000; ++i)
    //     o()
}

const offsetMap = new Map([
    ["JSFunction::executableOrRareData", 20n],
    ["FunctionExecutable::m_unlinkedExecutable", 60n],
    ["ExecutableBase::m_jitCodeForCall", 8n],
    ["JITCode::executableAddress", 20n],
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

    let value = read64(addrOf(o) + offset(field))

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
    let value = read64(addrOf(o) + offset(field))
    write64(addrOf(o) + offset(field), val)
    let newVal = read64(addrOf(o) + offset(field))
    output = true;

    if (verboseDeref)
        p(orig + " : 0x" + value.toString(16) + " -> 0x" + newVal.toString(16))
    return value
}

// -------------------------------------------------------------------------

let fnA = () => { p("A") }
let fnB = () => { p("B") }

inspectCell(fnA)
inspectCell(fnB)
p("---")

// If we enabled JIT, you could do this:
// deref(fnA, "JSFunction::executableOrRareData.ExecutableBase::m_jitCodeForCall.JITCode::executableAddress")
// and get different jit pointers for A and B
// Instead, we just change the executable pointer (which holds bytecode)

let a = deref(fnA, "JSFunction::executableOrRareData.FunctionExecutable::m_unlinkedExecutable")
p("A:")
hd(a)
p("B:")
hd(deref(fnB, "JSFunction::executableOrRareData.FunctionExecutable::m_unlinkedExecutable"))

p("---")

derefAssign(fnB, "JSFunction::executableOrRareData.FunctionExecutable::m_unlinkedExecutable", a)

p("---")

fnA()
fnB()

