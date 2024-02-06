function ROI = CreateCubeROI(nx, ny, nz, lx, ly, lz, CenterROI) % Создание массива ROI
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
