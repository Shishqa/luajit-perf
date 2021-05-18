-- fibonacci number
function payload(n)
  if n <= 1 then
    return n
  end
  return payload(n - 1) + payload(n - 2)
end
