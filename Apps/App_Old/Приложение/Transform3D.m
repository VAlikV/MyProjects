function [X, Y, Z, B] = Transform3D(lx, ly, lz, nx, ny, nz, Bdes) % Преобразование массива вида Node или ROI в трехмерный массив для построения
[X, Y, Z] = ndgrid(linspace(-lx/2,lx/2,nx),linspace(-ly/2,ly/2,ny),linspace(-lz/2,lz/2,nz));
B = reshape(Bdes,[nx,ny,nz]);    
