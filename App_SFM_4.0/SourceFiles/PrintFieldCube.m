function figField = PrintFieldCube( lx, ly, lz, nx, ny, nz, centerFOV, Bdes, level, plane, Lx, Ly, Lz, centerROI, figField) % Отрисовка целевого поля

[X,Y,Z,B] = Transform3D(lx, ly, lz, nx, ny, nz, centerFOV, Bdes); % Для отрисовки поля

if figField ~= 0
    figHandles = findall(groot, 'Type', 'figure');
    f = find(figHandles == figField);
    if ~isnan(f)
        close(figField)
    end
end

figField = figure('Name', 'Целевое поле' ,'NumberTitle','off', 'Position', [610 77 580 410]);
if (plane == "XY") % ---------------------------------------------------------- XY
    k = find(abs(Z(1,1,:)-level) < 0.00001);
    contourf(X(:,:,k)*1000, Y(:,:,k)*1000, B(:,:,k)*1000, 25)
    hold("on")
    rectangle('Position', [(-Lx*1000/2+centerROI(1)*1000) (-Ly*1000/2+centerROI(2)*1000) (Lx*1000) (Ly*1000)], 'LineStyle', '--')
    xlabel('x, мм'), ylabel('y, мм'), title(strcat('Целевое поле, мТ, z = ', num2str(level*1000), 'мм')) 
elseif (plane == "XZ") % ------------------------------------------------------ XZ 
    k = find(abs(Y(1,:,1)-level) < 0.00001);
    XX = reshape(X(:,k,:),[nx,nz,1]);
    ZZ = reshape(Z(:,k,:),[nx,nz,1]);
    BB = reshape(B(:,k,:),[nx,nz,1]);
    contourf(XX*1000, ZZ*1000, BB*1000, 25)
    hold("on")
    rectangle('Position', [(-Lx*1000/2+centerROI(1)*1000) (-Lz*1000/2+centerROI(3)*1000) (Lx*1000) (Lz*1000)], 'LineStyle', '--')
    xlabel('x, мм'), ylabel('z, мм'), title(strcat('Целевое поле, мТ, y = ', num2str(level*1000), 'мм'))
elseif (plane == "YZ") % ------------------------------------------------------ YZ
    k = find(abs(X(:,1,1)-level) < 0.00001);
    YY = reshape(Y(k,:,:),[ny,nz,1]);
    ZZ = reshape(Z(k,:,:),[ny,nz,1]);
    BB = reshape(B(k,:,:),[ny,nz,1]);
    contourf(YY*1000, ZZ*1000, BB*1000, 25)
    hold("on")
    rectangle('Position', [(-Ly*1000/2+centerROI(2)*1000) (-Lz*1000/2+centerROI(3)*1000) (Ly*1000) (Lz*1000)], 'LineStyle', '--')
    xlabel('y, мм'), ylabel('z, мм'), title(strcat('Целевое поле, мТ, x = ', num2str(level*1000), 'мм'))
else
    disp('___ОШИБКА ВЫБОРА ПЛОСКОСТИ___');
end
colorbar
axis('equal')
box("on")
grid("on") 
hold("off")
