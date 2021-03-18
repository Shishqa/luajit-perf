-- fibonacci number
function lua_payload(n) 
    if n == 0 then 
        return 0
    elseif n == 1 then
        return 1
    end
    return lua_payload(n - 1) + lua_payload(n - 2)
end
