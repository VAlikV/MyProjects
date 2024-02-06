function PrintDiffSphere(UI, lx, ly, lz, nx, ny, nz, centerFOV, Bdes, level, plane, Rsp, centerROI) % Отрисовка целевого поля

[X,Y,Z,B] = Transform3D(lx, ly, lz, nx, ny, nz, centerFOV, Bdes); % Для отрисовки поля

cla(UI)
if (plane == "XY") % ---------------------------------------------------------- XY
    k = find(abs(Z(1,1,:)-level) < 0.00001);

    r = sqrt(Rsp^2 - (level-centerROI(3))^2);
    theta=linspace(0,2*pi,200); 
    x=r*cos(theta) + centerROI(1); 
    y=r*sin(theta) + centerROI(2);

    contourf(UI,X(:,:,k)*1000, Y(:,:,k)*1000, B(:,:,k), 25)
    hold(UI,"on")
    plot(UI,x*1000,y*1000,'--k');
    xlabel(UI,'x, мм'), ylabel(UI,'y, мм'), title(UI,strcat('Разность, %, z = ', num2str(level*1000), 'мм')) 
elseif (plane == "XZ") % ------------------------------------------------------ XZ 
    k = find(abs(Y(1,:,1)-level) < 0.00001);
    
    r=sqrt(Rsp^2 - (level-centerROI(2))^2);
    theta=linspace(0,2*pi,200); 
    x=r*cos(theta) + centerROI(1); 
    y=r*sin(theta) + centerROI(3);
    
    XX = reshape(X(:,k,:),[nx,nz,1]);
    ZZ = reshape(Z(:,k,:),[nx,nz,1]);
    BB = reshape(B(:,k,:),[nx,nz,1]);
    
    contourf(UI,XX*1000, ZZ*1000, BB, 25)
    hold(UI,"on")
    plot(UI,x*1000,y*1000,'--k');
    xlabel(UI,'x, мм'), ylabel(UI,'z, мм'), title(UI,strcat('Разность, %, y = ', num2str(level*1000), 'мм'))
elseif (plane == "YZ") % ------------------------------------------------------ YZ
    k = find(abs(X(:,1,1)-level) < 0.00001);
    
    r=sqrt(Rsp^2 - (level-centerROI(1))^2);
    theta=linspace(0,2*pi,200); 
    x=r*cos(theta) + centerROI(2); 
    y=r*sin(theta) + centerROI(3);
    
    YY = reshape(Y(k,:,:),[ny,nz,1]);
    ZZ = reshape(Z(k,:,:),[ny,nz,1]);
    BB = reshape(B(k,:,:),[ny,nz,1]);
    
    contourf(UI,YY*1000, ZZ*1000, BB, 25)
    hold(UI,"on")
    plot(UI,x*1000,y*1000,'--k');
    xlabel(UI,'y, мм'), ylabel(UI,'z, мм'), title(UI,strcat('Разность, %, x = ', num2str(level*1000), 'мм'))
else
    disp('___ОШИБКА ВЫБОРА ПЛОСКОСТИ___');
end
colorbar(UI)
axis(UI,'equal')
box(UI,"on")
grid(UI,"on") 
hold(UI,"off")
