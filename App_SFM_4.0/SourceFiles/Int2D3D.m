function Int2D3D(Fi_int, L_int, I_int, Red, Blue, Red1, Blue1, Red2, Blue2) % Отрисовка 

figure('Name','Интерполированная потоковая функция','NumberTitle','off');    % Интерполированная функция 
movegui([1255 560]);
contourf(Fi_int,L_int,I_int)
box on
hold on
xlabel('fi'), ylabel('L'), title('Stream Function')
if ~isempty(Red)
    plot(Red(:,2), Red(:,1), '.r')
end
if ~isempty(Blue)
    plot(Blue(:,2), Blue(:,1), '.b')
end  
colorbar

figure('Name','Намотка 3D','NumberTitle','off');    % Намотка 3D 
movegui([1145 30]);
if ~isempty(Red1)
    plot3(Red1(:,1), Red1(:,2), Red1(:,3), '.r')
    hold on
end
if ~isempty(Blue1)
    plot3(Blue1(:,1), Blue1(:,2), Blue1(:,3), '.b')
end
box on
xlabel ('x [m]'), ylabel ('y [m]'), zlabel ('z [m]')
axis equal
grid on 

figure('Name','Намотка 2D','NumberTitle','off');     % Намотка 2D 
movegui([1255 30]);
if ~isempty(Red2)
    plot(Red2(:,2), Red2(:,1), '.r')
    hold on
end
if ~isempty(Blue2)
    plot(Blue2(:,2), Blue2(:,1), '.b')
end
box on
xlabel ('r [m]'), ylabel ('x [m]')
axis equal
grid on 
