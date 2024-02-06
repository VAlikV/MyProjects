function figRes = PrintResults2(R, L, px, py, axial, Fi, Ll, II, Red1, Blue1, Red2, Blue2, mode, figRes) % Инетерполяция потоковой функции и контур с током

W = 2*pi*R*1000;
LL = L*1000;

if figRes ~= 0
    figHandles = findall(groot, 'Type', 'figure');
    f = find(figHandles == figRes);
    if ~isnan(f)
        close(figRes)
    end
end

figRes = figure('Name', 'Результат' ,'NumberTitle','off', 'Position', [1200 577 580 410]);
switch mode
    case 2 % "Потоковая функция"

        contourf(Fi,Ll,II);
        box("on")
        xlabel('fi'), ylabel('L, м'), title('Потоковая функция')
        colorbar

    case 3 % "Потоковая функция + Grad"

        contourf(Fi,Ll,II);
        box("on")
        hold("on")
        quiver(Fi,Ll,px,py,0.2,'*r', 'MarkerSize', 2)
        xlabel('fi'), ylabel('L, м'), title('Потоковая функция + Grad')
        colorbar
        hold("off")

    case 0 % "Намотка 2D"

        if ~isempty(Red2)
            plot(Red2(:,2)*1000, Red2(:,1)*1000, '.r','MarkerSize',1)
            hold("on")
        end
        if ~isempty(Blue2)
            plot(Blue2(:,2)*1000, Blue2(:,1)*1000, '.b','MarkerSize',1)
        end
        
        if axial
            xlabel('r, мм'), ylabel('z, мм')
        else 
            xlabel('r, мм'), ylabel('x, мм')
        end
        title('Намотка 2D')
        rectangle('Position', [-W/2 -LL W 2*LL])
        box("on")
        axis("equal")
        grid("on")
        hold("off")

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
            plot3( Red1(:,1)*1000, Red1(:,2)*1000, Red1(:,3)*1000, '.r','MarkerSize',1)
            hold("on")
        end
        if ~isempty(Blue1)
            plot3(Blue1(:,1)*1000, Blue1(:,2)*1000, Blue1(:,3)*1000, '.b','MarkerSize',1)
        end
        box("on")
        xlabel('x, мм'), ylabel('y, мм'), zlabel('z, мм'), title('Намотка 3D')
        axis("equal")
        grid("on")
        hold("off")
end
end
     
