-----------------------------------------------
local jit = require("jit")
local ffi = require("ffi")
local os = require("os")
local io = require("io")
-----------------------------------------------

local lua = require "lua_payload"

-- mind project-specific package location --
local c = ffi.load("c_payload")

ffi.cdef[[
double c_payload(double n);
]]

------------------------------------------------

local start_time = os.clock()
local benchmark_time = 1000

local i = 0
while os.clock() - start_time < benchmark_time do
    if i % 2 == 0 then
        c.c_payload(20)
    else
        lua.payload(20)
    end
    i = i + 1
end

-----------------------------------------------
