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
-- mind project-specific package location --
c_payload = ffi.load("c_payload")

ffi.cdef[[
double c_payload(double n);
]]

local payload = require("lua_payload")

------------------------------------------------

config({use_jit=false, time=20})

print("- running...")

local start_time = os.clock()

local i = 0
while i < 10000000000 do
    if i % 2 == 0 then
        c_payload.c_payload(10)
    else
        lua_payload(10)
    end
    i = i + 1
end

print("- done\n")

-----------------------------------------------
