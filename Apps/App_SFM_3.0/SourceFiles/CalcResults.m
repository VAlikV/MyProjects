function CalcResults(UI, R, L, nfi, nL, axial, I, Nc, eb, er, zeror, mode) % Инетерполяция потоковой функции и контур с током

[Fi, Ll, II] = Transform2D(L, nfi, nL, I);
[px,py] = gradient(II);
p=max(max(sqrt(px.^2+py.^2)));
px = px/(p);
py = py/(p);
            
[Fi_int, L_int, I_int, Red, Blue, Red1, Blue1, Red2, Blue2] = InterpCircuit(R, L, nfi, nL, I, Nc, eb, er, zeror);
end
     
