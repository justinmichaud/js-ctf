#!/usr/bin/env node
"use strict";

console.log("Don't forget to run `make all` before running this script");

const path = require("path");
const fs = require("fs");
const V86 = require("./../../../build/libv86.js").V86;

const V86_ROOT = path.join(__dirname, "../../..");
const OUTPUT_FILE = path.join(V86_ROOT, "images/alpine-state.bin");

var emulator = new V86({
    bios: { url: path.join(V86_ROOT, "bios/seabios.bin") },
    vga_bios: { url: path.join(V86_ROOT, "bios/vgabios.bin") },
    autostart: true,
    memory_size: 512 * 1024 * 1024,
    vga_memory_size: 8 * 1024 * 1024,
    network_relay_url: "<UNUSED>",
    bzimage_initrd_from_filesystem: true,
    cmdline: "rw root=host9p rootfstype=9p rootflags=trans=virtio,cache=loose modules=virtio_pci tsc=reliable init_on_free=on",
    filesystem: {
        baseurl: path.join(V86_ROOT, "images/alpine-rootfs-flat"),
        basefs: path.join(V86_ROOT, "images/alpine-fs.json"),
    },
    screen_dummy: true,
});

console.log("Now booting, please stand by ...");

let serial_text = "";
let booted = false;

emulator.add_listener("serial0-output-byte", function(byte)
{
    const c = String.fromCharCode(byte);
    //process.stdout.write(c);

    serial_text += c;

    if(!booted && serial_text.endsWith("localhost:~# "))
    {
        booted = true;

        emulator.serial0_send("echo \"LD_LIBRARY_PATH=/root gdb --args /root/jsc 0.js\" > .ash_history\n");
        emulator.serial0_send("sync;echo 3 >/proc/sys/vm/drop_caches\n");

        setTimeout(async function ()
            {
                const s = await emulator.save_state();

                fs.writeFile(OUTPUT_FILE, new Uint8Array(s), function(e)
                    {
                        if(e) throw e;
                        console.log("Saved as " + OUTPUT_FILE);
                        emulator.stop();
                    });
            }, 10 * 1000);
    }
});
