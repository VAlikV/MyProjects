clc
close all 
clear all

% ------------------------------------------------------------------- Контур

R = 0.07; % Радиус
n = 10;

data1 = readtable('YZ_1.txt');
data = table2array(data1)./1000;
YZ1 = zeros(length(data(:,1)),3);
YZ1(:,1) = data(:,2);
YZ1(:,2) = data(:,1);
YZ1 = transZ(YZ1,R);
YZ1 = InterpCoil(YZ1, n);
YZ1 = flex(YZ1,R);

data1 = readtable('YZ_2.txt');
data = table2array(data1)./1000;
YZ2 = zeros(length(data(:,1)),3);
YZ2(:,1) = data(:,2);
YZ2(:,2) = data(:,1);
YZ2 = transZ(YZ2,R);
YZ2 = InterpCoil(YZ2, n);
YZ2 = flex(YZ2,R);
%Blue = rotX(Blue, -pi/2);

data1 = readtable('YZ_3.txt');
data = table2array(data1)./1000;
YZ3 = zeros(length(data(:,1)),3);
YZ3(:,1) = data(:,2);
YZ3(:,2) = data(:,1);
YZ3 = transZ(YZ3,R);
YZ3 = InterpCoil(YZ3, n);
YZ3 = flex(YZ3,R);
%Green = invY(Green);

data1 = readtable('YZ_4.txt');
data = table2array(data1)./1000;
YZ4 = zeros(length(data(:,1)),3);
YZ4(:,1) = data(:,2);
YZ4(:,2) = data(:,1);
YZ4 = transZ(YZ4,R);
YZ4 = InterpCoil(YZ4, n);
YZ4 = flex(YZ4,R);
% Viol = rotX(Viol, pi/2);

data1 = readtable('YZ_5.txt');
data = table2array(data1)./1000;
YZ5 = zeros(length(data(:,1)),3);
YZ5(:,1) = data(:,2);
YZ5(:,2) = data(:,1);
YZ5 = transZ(YZ5,R);
YZ5 = InterpCoil(YZ5, n);
YZ5 = flex(YZ5,R);

data1 = readtable('YZ_6.txt');
data = table2array(data1)./1000;
YZ6 = zeros(length(data(:,1)),3);
YZ6(:,1) = data(:,2);
YZ6(:,2) = data(:,1);
YZ6 = transZ(YZ6,R);
YZ6 = InterpCoil(YZ6, n);
YZ6 = flex(YZ6,R);

% ------------------------------------------------------------------- ROI

nx = 15;    % Кол-во точек вдоль Х
ny = 15;    % Кол-во точек вдоль Y
nz = 15;    % Кол-во точек вдоль Z
K = nx*ny*nz;  % Полное число точек ROI

lx = 0.05;  % Длина области вдоль Х
ly = 0.05;  % Длина области вдоль Y
lz = 0.05;  % Длина области вдоль Z

CenterROI = [0 0 0]; % Положение центра ROI

ROI = CreateROI(nx, ny, nz, lx, ly, lz, CenterROI);

level = 0.0;  % Положение плоскости
plane = 2;  % Выбор плоскости 0)XY, 1)XZ, 2)YZ

if plane == 0
    disp(linspace(-lz/2, lz/2, nz)+CenterROI(3));
elseif plane == 1
    disp(linspace(-ly/2, ly/2, ny)+CenterROI(2));
elseif plane == 2
    disp(linspace(-lx/2, lx/2, nx)+CenterROI(1));
end

I = 10;

% ------------------------------------------------------------------- Расчет

dr = 1e-5;
B = BSL(YZ1, I, ROI);
B = B + BSL(YZ2, I, ROI);
B = B + BSL(YZ3, I, ROI);
B = B + BSL(YZ4, I, ROI);
B = B + BSL(YZ5, I, ROI);
B = B + BSL(YZ6, I, ROI);

PrintField(lx, ly, lz, nx, ny, nz, CenterROI, B(:,3), level, plane)

% ------------------------------------------------------------------- Отрисовка

figure('Name','Контур','NumberTitle','off'); 
plot3(YZ1(:,1),YZ1(:,2),YZ1(:,3),'b-');
hold on
plot3(ROI(:,1),ROI(:,2),ROI(:,3),'k.');

plot3(YZ2(:,1),YZ2(:,2),YZ2(:,3),'r-')  % 'r-'
plot3(YZ3(:,1),YZ3(:,2),YZ3(:,3),'b-')  % 'b-'
plot3(YZ4(:,1),YZ4(:,2),YZ4(:,3),'r-')  % 'r-'
plot3(YZ5(:,1),YZ5(:,2),YZ5(:,3),'b-')  % 'b-'
plot3(YZ6(:,1),YZ6(:,2),YZ6(:,3),'r-')  % 'r-'
xlabel ('x [m]'), ylabel ('y [m]'), zlabel ('z [m]')
axis equal
grid on 

% ------------------------------------------------------------------- Функции

function Coil1 = InterpCoil(Coil, n)
    Coil1 = zeros((length(Coil(:,1))+(length(Coil(:,1))-1)*(n-2)),3);
    for i=1:(length(Coil(:,1))-1)
        Coil1(((i-1)*(n-1))+1:(i*(n-1)+1),1) = linspace(Coil(i,1),Coil(i+1,1),n);
        Coil1(((i-1)*(n-1))+1:(i*(n-1)+1),2) = linspace(Coil(i,2),Coil(i+1,2),n);
        Coil1(((i-1)*(n-1))+1:(i*(n-1)+1),3) = linspace(Coil(i,3),Coil(i+1,3),n);
    end
end

function B = BSL(Coil, I, ROI)
    B = zeros(length(ROI(:,1)),3);
    for i = 1:(length(Coil(:,1))-1)
        dlx = Coil(i+1,1) - Coil(i,1);
        dly = Coil(i+1,2) - Coil(i,2);
        dlz = Coil(i+1,3) - Coil(i,3);
        [dx, dy, dz] = Distance(Coil(i,:), ROI);
        B(:,1) = B(:,1) + (10^(-7))*(I*(dly*dz-dlz*dy))./(sqrt(dx.^2 + dy.^2 + dz.^2)).^3;
        B(:,2) = B(:,2) + (10^(-7))*(I*(dlz*dx-dlx*dz))./(sqrt(dx.^2 + dy.^2 + dz.^2)).^3;
        B(:,3) = B(:,3) + (10^(-7))*(I*(dlx*dy-dly*dx))./(sqrt(dx.^2 + dy.^2 + dz.^2)).^3;
    end
end

function PrintField(lx, ly, lz, nx, ny, nz, centerROI, Bz, level, plane) % Отрисовка полученного поля 
    
    [X1,Y1,Z1,Bz] = Transform3D(lx, ly, lz, nx, ny, nz, centerROI, Bz);

    figure('Name','Полученное поле','NumberTitle','off'); 
    movegui([570 30]);
    if (plane == 0) % ---------------------------------------------------------- XY
        k = find(abs(Z1(1,1,:)-level) < 0.00001);
        contourf(X1(:,:,k), Y1(:,:,k), Bz(:,:,k), 20)
        xlabel ('x [m]'), ylabel ('y [m]'), title(strcat('Bz [T], z = ', num2str(level))) 
    elseif (plane == 1) % ------------------------------------------------------ XZ
        k = find(abs(Y1(1,:,1)-level) < 0.00001);
        XX1 = reshape(X1(:,k,:),[nx,nz,1]);
        ZZ1 = reshape(Z1(:,k,:),[nx,nz,1]);
        BB1 = reshape(Bz(:,k,:),[nx,nz,1]);
        contourf(XX1, ZZ1, BB1, 20)
        xlabel ('x [m]'), ylabel ('z [m]'), title(strcat('Bz [T], y = ', num2str(level)))
    elseif (plane == 2) % ------------------------------------------------------ YZ
        k = find(abs(X1(:,1,1)-level) < 0.00001);
        YY1 = reshape(Y1(k,:,:),[ny,nz,1]);
        ZZ1 = reshape(Z1(k,:,:),[ny,nz,1]);
        BB1 = reshape(Bz(k,:,:),[ny,nz,1]);
        contourf(YY1, ZZ1, BB1, 20)
        xlabel ('y [m]'), ylabel ('z [m]'), title(strcat('Bz [T], x = ', num2str(level)))
    else
        disp('___ОШИБКА ВЫБОРА ПЛОСКОСТИ___');
    end
    colorbar
    axis equal
    box on
    grid on

end

function ROI = CreateROI(nx, ny, nz, lx, ly, lz, CenterROI) % Создание кубического массива ROI
    ROI = [];
    dy = ly/(ny-1);
    dz = lz/(nz-1);
    for j = 1:nz
        z = -lz/2+(j-1)*dz;
        for i = 1:ny
            y = -ly/2+(i-1)*dy;
            Temp = [transpose(linspace(-lx/2,lx/2,nx))+CenterROI(1) y*ones(nx,1)+CenterROI(2) z*ones(nx,1)+CenterROI(3)];
            ROI = [ROI; Temp];
        end
    end
end

function di = DistanceROI(Node, ROI) 
    di = sqrt((Node(1)-ROI(:,1)).^2+(Node(2)-ROI(:,2)).^2+(Node(3)-ROI(:,3)).^2);
end

function [dx, dy, dz] = VectorDistanceROI(Node, ROI) % Расстояние между двумя узлами
    dx = (Node(1)-ROI(:,1));
    dy = (Node(2)-ROI(:,2));
    dz = (Node(3)-ROI(:,3));
end

function [X, Y, Z, B] = Transform3D(lx, ly, lz, nx, ny, nz, center, Bdes) % Преобразование массива вида Node или ROI в трехмерный массив для построения
    [X, Y, Z] = ndgrid(linspace(-lx/2,lx/2,nx)+center(1),linspace(-ly/2,ly/2,ny)+center(2),linspace(-lz/2,lz/2,nz)+center(3));
    B = reshape(Bdes,[nx,ny,nz]);    
end

function Coil = rotX(Coil, a)
    M = [1 0 0; 0 cos(a) -sin(a); 0 sin(a) cos(a)];
    for i = 1:length(Coil(:,1))
        Coil(i,:) = Coil(i,:)*M;
    end
end

function Coil = rotY(Coil, a)
    M = [cos(a) 0 sin(a); 0 1 0; -sin(a) 0 cos(a)];
    for i = 1:length(Coil(:,1))
        Coil(i,:) = Coil(i,:)*M;
    end
end

function Coil = rotZ(Coil, a)
    M = [cos(a) -sin(a) 0; sin(a) cos(a) 0; 0 0 1];
    for i = 1:length(Coil(:,1))
        Coil(i,:) = Coil(i,:)*M;
    end
end

function Coil = invX(Coil)
    Coil(:,1) = -Coil(:,1);
end

function Coil = invY(Coil)
    Coil(:,2) = -Coil(:,2);
end

function Coil = invZ(Coil)
    Coil(:,3) = -Coil(:,3);
end

function Coil = transX(Coil, X)
    Coil(:,1) = Coil(:,1) + X;
end

function Coil = transY(Coil, Y)
    Coil(:,2) = Coil(:,2) + Y;
end

function Coil = transZ(Coil, Z)
    Coil(:,3) = Coil(:,3) + Z;
end

function Coil = flex(Coil,R)
    Len = length(Coil(:,1));
    for i = 1:(Len)
        y = Coil(i,2);
        Coil(i,1)=Coil(i,1);
        Coil(i,2)=R*sin(y/R);
        Coil(i,3)=R*(cos(y/R));
    end
    Coil = real(Coil);
end

function [Coil, S] = Spiral(n_points, n_vit, R, L)
% n_points - кол-во точек в витке
% n_vit - кол-во витков
S = 0;                  % Длина катушки 
N = n_points*n_vit;     % Кол-во точек в катушке

Coil = zeros(N,3);

fi = linspace(0, 2*pi*(n_vit-1), N);
len = linspace(0, L, N);

Coil(:,1) = R*cos(fi);
Coil(:,2) = R*sin(fi);
Coil(:,3) = len;

for i = 2:length(Coil(:,1)) % Определение длины
    ds = sqrt((Coil(i-1,1)-Coil(i,1))^2 + (Coil(i-1,2)-Coil(i,2))^2 + (Coil(i-1,2)-Coil(i,2))^2);
    S = S + ds;
end

end

