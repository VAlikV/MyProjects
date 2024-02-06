function [Fi, L, II] = Transform2D(L, nfi, nL, I) % Преобразование массива I в двумерный массив для построения
[Fi, L] = meshgrid(linspace(-pi,pi,nfi+1), linspace(-L,L,nL));
II = reshape(I,[nfi,nL]);
II = [II(nfi,:); II];
II = transpose(II);
