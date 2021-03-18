-----------------------------------------------
local jit = require("jit")
local ffi = require("ffi")
local os = require("os")
local io = require("io")
-----------------------------------------------

benchmark_time = 0

function config(args)
    print("- config")

    io.write("\t-JIT: ")
    if args.use_jit == true then
        jit.on()
        print("on")
    else
        jit.off()
        print("off")
    end

    benchmark_time = args.time
    print("\t-time: "..benchmark_time.." sec");
end

-----------------------------------------------

c_payload = ffi.load("lib/libc_payload.so")

ffi.cdef[[
double c_payload(double n);
]]

local payload = require("lua_payload")

-----------------------------------------------
config{use_jit=true, time=60}
-----------------------------------------------

print("- running...")

local os = require("os")
local start_time = os.clock()

local i = 0
while os.clock() - start_time < benchmark_time do
    if i % 2 == 0 then
        c_payload.c_payload(15)
    else
        lua_payload(15)
    end
    i = i + 1
end

print("- done\n")

-----------------------------------------------
