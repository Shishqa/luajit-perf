local jit = require("jit")
local os = require("os")

benchmark_time = 0

function config(args)
    print("- config")

    if args.use_jit == true then
        jit.on()
        print("\t-JIT on")
    else
        jit.off()
        print("\t-JIT off")
    end

    benchmark_time = args.time
    print("\t-time: "..benchmark_time);
end
