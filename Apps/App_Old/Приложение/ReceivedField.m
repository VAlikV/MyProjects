function [Bz, DES] = ReceivedField(I, K, N, S, Node, ROI, Bdes) % Расчет и отрисовка полученного поля

Bz = zeros(K,1);
Temp = 0;
for j = 1:N
    b = Calcbz(j, S, Node, ROI);
    Temp = Temp + I(j,1)*b;
end
Bz(:,1) = Temp;

DES = Bdes - Bz;

%level, plane, lx, ly, lz, nx, ny, nz
%[X1,Y1,Z1,Bz] = Transform3D(lx, ly, lz, nx, ny, nz, Bz);

% figure('Name','Полученное поле','NumberTitle','off'); 
% movegui([570 30]);
% if (plane == 0) % ---------------------------------------------------------- XY
%     k = find(abs(Z1(1,1,:)-level) < 0.00001);
%     surf(X1(:,:,k), Y1(:,:,k), Bz(:,:,k))
%     xlabel ('x [m]'), ylabel ('y [m]'), title(strcat('Bz [T], z = ', num2str(level))) 
% elseif (plane == 1) % ------------------------------------------------------ XZ
%     k = find(abs(Y1(1,:,1)-level) < 0.00001);
%     XX1 = reshape(X1(:,k,:),[nx,nz,1]);
%     ZZ1 = reshape(Z1(:,k,:),[nx,nz,1]);
%     BB1 = reshape(Bz(:,k,:),[nx,nz,1]);
%     surf(XX1, ZZ1, BB1)
%     xlabel ('x [m]'), ylabel ('z [m]'), title(strcat('Bz [T], y = ', num2str(level)))
% elseif (plane == 2) % ------------------------------------------------------ YZ
%     k = find(abs(X1(:,1,1)-level) < 0.00001);
%     YY1 = reshape(Y1(k,:,:),[ny,nz,1]);
%     ZZ1 = reshape(Z1(k,:,:),[ny,nz,1]);
%     BB1 = reshape(Bz(k,:,:),[ny,nz,1]);
%     surf(YY1, ZZ1, BB1)
%     xlabel ('y [m]'), ylabel ('z [m]'), title(strcat('Bz [T], x = ', num2str(level)))
% else
%     disp('___ОШИБКА ВЫБОРА ПЛОСКОСТИ___');
% end
% colorbar
% box on
% grid on
