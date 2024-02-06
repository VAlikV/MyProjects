clc
clear all 
close all
tic
%% ------------------------------------------------------------------------- Создание ROI
Centre = [0, 0, 0.05];

nx = 15;    % Кол-во точек вдоль Х
ny = 15;    % Кол-во точек вдоль Y
nz = 15;    % Кол-во точек вдоль Z
lx = 0.01;  % Длина области вдоль Х
ly = 0.0015;  % Длина области вдоль Y
lz = 0.00001;  % Длина области вдоль Z
ROI = [];

level = 8;  % Положение плоскости
plane = 2;  % Выбор плоскости 0)XY, 1)XZ, 2)YZ

K = nx*ny*nz;  % Полное число точек ROI
dy = ly/(ny-1);
dz = lz/(nz-1);
for j = 1:nz
    z = -lz/2+(j-1)*dz;
    for i = 1:ny
        y = -ly/2+(i-1)*dy;
        Temp = [transpose(linspace(-lx/2,lx/2,nx))+Centre(1) y*ones(nx,1)+Centre(2) z*ones(nx,1)+Centre(3)];
        ROI = [ROI; Temp];
    end
end

%% ------------------------------------------------------------------------- Параметры первого магнита

D = 0.011;
Moment1 = [0, 0, 0.09];
ro = 5/0.02;             % Плотность магнитных моментов
ml1 = [0.06 0.08 0.04];  % Размеры магнита 
%m1 = [round(ro*ml1(1)) round(ro*ml1(2)) round(ro*ml1(3))];    % Кол-во точек
m1 = [21 21 21];
MagPos1 = [-(ml1(1)+D)/2, 0, 0];

%% ------------------------------------------------------------------------- Параметры второго магнита

Moment2 = [0, 0, -0.09];
ml2 = [0.06 0.08 0.04];  % Размеры магнита
%m2 = [round(ro*ml2(1)) round(ro*ml2(2)) round(ro*ml2(3))];    % Кол-во точек
m2 = [21 21 21];
MagPos2 = [(ml2(1)+D)/2, 0, 0];

%% ------------------------------------------------------------------------- Магнитный момент
Mag = CalcMag(MagPos1, m1, ml1, Moment1);
Mag1 = CalcMag(MagPos2, m2, ml2, Moment2);
Mag = [Mag; Mag1];

B = zeros(K,3);
Temp = B;

for i=1:length(Mag(:,1,1))
    Rx = ROI(:,1) - Mag(i,1,2);
    Ry = ROI(:,2) - Mag(i,2,2);
    Rz = ROI(:,3) - Mag(i,3,2);
    Temp(:,1) = ((3*Rx.*ScalarP(Mag(i,:,1),[Rx Ry Rz]) - Mag(i,1,1).*RadiusV([Rx Ry Rz]).^2)./RadiusV([Rx Ry Rz]).^5)*1e-7;
    Temp(:,2) = ((3*Ry.*ScalarP(Mag(i,:,1),[Rx Ry Rz]) - Mag(i,2,1).*RadiusV([Rx Ry Rz]).^2)./RadiusV([Rx Ry Rz]).^5)*1e-7;
    Temp(:,3) = ((3*Rz.*ScalarP(Mag(i,:,1),[Rx Ry Rz]) - Mag(i,3,1).*RadiusV([Rx Ry Rz]).^2)./RadiusV([Rx Ry Rz]).^5)*1e-7;
    B = B + Temp;
end

[X, Y, Z, Hx, Hy, Hz] = Transform3D(lx, ly, lz, nx, ny, nz, Centre, B(:,1), B(:,2), B(:,3));
normH = 1;%sqrt(Hx.^2+Hy.^2+Hz.^2);

H = Hx.^2+Hy.^2+Hz.^2;

%% ------------------------------------------------------------------------- Отрисовка поля
 
[X1, Y1, Z1, AvgH, des, HH] = Display(X, Y, Z, H, nx, ny, nz, level, plane);
T = 1/(42*(max(HH,[],'all')-min(HH,[],'all')));
disp(strcat("Время расфазировки: ", num2str(T), " мкс"))
disp(strcat("Среднее поле: ", num2str(AvgH)))
disp(strcat("Отклонение:  ", num2str(des)))

%% ------------------------------------------------------------------------- Отрисовка векторов

figure('Name','Область','NumberTitle','off')
%plot3(ROI(:,1), ROI(:,2), ROI(:,3),'.k')
quiver3(X,Y,Z,Hx./normH,Hy./normH,Hz./normH,'b')
hold on
plot3(X1(:),Y1(:),Z1(:),'r*');
quiver3(Mag(:,1,2),Mag(:,2,2),Mag(:,3,2),Mag(:,1,1),Mag(:,2,1),Mag(:,3,1),'k')
xlabel ('x [m]'), ylabel ('y [m]'), zlabel ('z [m]')
axis equal
grid on 

toc
function R = RadiusV(A) % Радиус вектор точки
    R = sqrt(A(:,1).^2 + A(:,2).^2 + A(:,3).^2);
end

function p = ScalarP(Vector1, Vector2) % Скалярное произведение
    p = Vector1(:,1).*Vector2(:,1) + Vector1(:,2).*Vector2(:,2) + Vector1(:,3).*Vector2(:,3);
end

function [X, Y, Z, Bx, By, Bz] = Transform3D(lx, ly, lz, nx, ny, nz, Centre, Bx1, By1, Bz1) % Преобразование массива вида Node или ROI в трехмерный массив для построения
    [X, Y, Z] = ndgrid(linspace(-lx/2,lx/2,nx)+Centre(1),linspace(-ly/2,ly/2,ny)+Centre(2),linspace(-lz/2,lz/2,nz)+Centre(3));
    Bx = reshape(Bx1,[nx,ny,nz]);   
    By = reshape(By1,[nx,ny,nz]);  
    Bz = reshape(Bz1,[nx,ny,nz]);  
end

function Mag = CalcMag(MagPos, m, ml, Moment)
    M = [];
    mdy = ml(2)/(m(2)-1);
    mdz = ml(3)/(m(3)-1);
    for j = 1:m(3)
        z = -ml(3)/2+(j-1)*mdz;
        for i = 1:m(2)
            y = -ml(2)/2+(i-1)*mdy;
            Temp = [transpose(linspace(-ml(1)/2,ml(1)/2,m(1)))+MagPos(1) y*ones(m(1),1)+MagPos(2) z*ones(m(1),1)+MagPos(3)];
            M = [M; Temp];
        end
    end
    Mag = zeros(m(1)*m(2)*m(3),3,2); 
    Mag(:,:,2) = M;
    Mag(:,1,1) = Moment(1);
    Mag(:,2,1) = Moment(2);
    Mag(:,3,1) = Moment(3);
end

function [X1, Y1, Z1, AvgH, des, HH] = Display(X, Y, Z, H, nx, ny, nz, level, plane)

    k = level;
    figure(3)
    movegui([570 560]);
    if (plane == 0) % ---------------------------------------------------------- XY
        %k = find(Z_M(1,1,:)==level);
        X1 = X(:,:,k);
        Y1 = Y(:,:,k);
        Z1 = Z(:,:,k);
        surf(X(:,:,k), Y(:,:,k), H(:,:,k))
        xlabel ('x [m]'), ylabel ('y [m]'), title(strcat('Bz [T], z = ', num2str(level)))
        MaxH = max(H(:,:,k),[],'all');
        MinH = min(H(:,:,k),[],'all');
        HH = H(:,:,k);
        AvgH = (MaxH+MinH)/2;
        des = max(abs(H(:,:,k)-AvgH)./AvgH,[],'all')*100;
    elseif (plane == 1) % ------------------------------------------------------ XZ 
        %k = find(Y_M(1,:,1)==level);
        XX = reshape(X(:,k,:),[nx,nz,1]);
        ZZ = reshape(Z(:,k,:),[nx,nz,1]);
        HH = reshape(H(:,k,:),[nx,nz,1]);
        X1 = X(:,k,:);
        Y1 = Y(:,k,:);
        Z1 = Z(:,k,:);
        surf(XX, ZZ, HH)
        xlabel ('x [m]'), ylabel ('z [m]'), title(strcat('Bz [T], y = ', num2str(level)))
        MaxH = max(HH,[],'all');
        MinH = min(HH,[],'all');
        AvgH = (MaxH+MinH)/2;
        des = max(abs(HH-AvgH)./AvgH,[],'all')*100;
    elseif (plane == 2) % ------------------------------------------------------ YZ
        %k = find(X(:,1,1)==level);
        YY = reshape(Y(k,:,:),[ny,nz,1]);
        ZZ = reshape(Z(k,:,:),[ny,nz,1]);
        HH = reshape(H(k,:,:),[ny,nz,1]);
        X1 = X(k,:,:);
        Y1 = Y(k,:,:);
        Z1 = Z(k,:,:);
        surf(YY, ZZ, HH)
        xlabel ('y [m]'), ylabel ('z [m]'), title(strcat('Bz [T], x = ', num2str(level)))
        MaxH = max(HH,[],'all');
        MinH = min(HH,[],'all');
        AvgH = (MaxH+MinH)/2;
        des = max(abs(HH-AvgH)./AvgH,[],'all')*100;
    else
        disp('___ОШИБКА ВЫБОРА ПЛОСКОСТИ___');
    end
    colorbar
    box on
    hold on
    grid on

end


