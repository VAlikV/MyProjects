function [px, py, Fi, Ll, II, Red1, Blue1, Red2, Blue2] = PrintResults(UI, R, L, nfi, nL, axial, I, Nc, eb, er, zeror, mode) % Инетерполяция потоковой функции и контур с током

[Fi, Ll, II] = Transform2D(L, nfi, nL, I);
[px,py] = gradient(II);
p = 1;%max(sqrt(px.^2+py.^2), [],'all');
px = px/(p);
py = py/(p);
            
[Fi_int, L_int, I_int, Red, Blue, Red1, Blue1, Red2, Blue2] = InterpCircuit(R, L, nfi, nL, I, Nc, eb, er, zeror);
W = 2*pi*R*1000;
LL = L*1000;

cla(UI, 'reset')
switch mode
    case 2 % "Потоковая функция"

        contourf(UI,Fi,Ll*1000,II);
        %box(UI,"on")
        xlabel(UI,'fi'), ylabel(UI,'L, мм')
        colorbar(UI)

    case 3 % "Потоковая функция + Grad"

        contourf(UI,Fi,Ll*1000,II);
        %box(UI,"on")
        hold(UI,"on")
        quiver(UI,Fi,Ll*1000,px,py,0.2,'*r', 'MarkerSize', 2)
        xlabel(UI,'fi'), ylabel(UI,'L, мм')
        colorbar(UI)
        hold(UI,"off")

    case 0 % "Намотка 2D"

        if ~isempty(Red2)
            plot(UI,Red2(:,2)*1000, Red2(:,1)*1000, '.r','MarkerSize',1)
            hold(UI,"on")
        end
        if ~isempty(Blue2)
            plot(UI,Blue2(:,2)*1000, Blue2(:,1)*1000, '.b','MarkerSize',1)
        end
        
        if axial
            xlabel(UI,'r, мм'), ylabel(UI,'z, мм')
        else 
            xlabel(UI,'r, мм'), ylabel(UI,'x, мм')
        end
        
        rectangle(UI,'Position', [-W/2 -LL W 2*LL])
        axis(UI,"equal")
        grid(UI,"on")
        hold(UI,"off")

    case 1 % "Намотка 3D"
        if axial  
            if ~isempty(Red1)
                Red1 = rotY(Red1, pi/2);
            end
            if ~isempty(Blue1)
                Blue1 = rotY(Blue1, pi/2);
            end
        end
        if ~isempty(Red1)
            plot3(UI, Red1(:,1)*1000, Red1(:,2)*1000, Red1(:,3)*1000, '.r','MarkerSize',1)
            hold(UI,"on")
        end
        if ~isempty(Blue1)
            plot3(UI,Blue1(:,1)*1000, Blue1(:,2)*1000, Blue1(:,3)*1000, '.b','MarkerSize',1)
        end
        %box(UI,"on")
        xlabel(UI,'x, мм'), ylabel(UI,'y, мм'), zlabel(UI,'z, мм')
        axis(UI,"equal")
        grid(UI,"on")
        hold(UI,"off")
end
end
     
