function TargetField(lx, ly, lz, nx, ny, nz, Bdes, level, plane) % Отрисовка целевого поля

[X,Y,Z,B] = Transform3D(lx, ly, lz, nx, ny, nz, Bdes); % Для отрисовки поля

figure('Name','Целевое поле','NumberTitle','off'); 
movegui([570 560]);
if (plane == 0) % ---------------------------------------------------------- XY
    k = find(abs(Z(1,1,:)-level) < 0.00001);
    surf(X(:,:,k), Y(:,:,k), B(:,:,k))
    xlabel ('x [m]'), ylabel ('y [m]'), title(strcat('Bz [T], z = ', num2str(level))) 
elseif (plane == 1) % ------------------------------------------------------ XZ 
    k = find(abs(Y(1,:,1)-level) < 0.00001);
    XX = reshape(X(:,k,:),[nx,nz,1]);
    ZZ = reshape(Z(:,k,:),[nx,nz,1]);
    BB = reshape(B(:,k,:),[nx,nz,1]);
    surf(XX, ZZ, BB)
    xlabel ('x [m]'), ylabel ('z [m]'), title(strcat('Bz [T], y = ', num2str(level)))
elseif (plane == 2) % ------------------------------------------------------ YZ
    k = find(abs(X(:,1,1)-level) < 0.00001);
    YY = reshape(Y(k,:,:),[ny,nz,1]);
    ZZ = reshape(Z(k,:,:),[ny,nz,1]);
    BB = reshape(B(k,:,:),[ny,nz,1]);
    surf(YY, ZZ, BB)
    xlabel ('y [m]'), ylabel ('z [m]'), title(strcat('Bz [T], x = ', num2str(level)))
else
    disp('___ОШИБКА ВЫБОРА ПЛОСКОСТИ___');
end
colorbar
box on
grid on 
