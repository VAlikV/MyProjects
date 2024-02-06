function StreamFunctionGrad(L, nfi, nL, I) % Отрисовка потоковой функции и градиента п.ф.

[Fi, Ll, II] = Transform2D(L, nfi, nL, I);
[px,py] = gradient(II);
p=max(max(sqrt(px.^2+py.^2)));
px = px/(p);
py = py/(p);

figure('Name','Потоковая функция','NumberTitle','off'); 
movegui([1145 560]);
contourf(Fi,Ll,II);
box on
hold on
quiver(Fi,Ll,px,py,0.2,'*r', 'MarkerSize', 3, 'LineWidth', 1)
xlabel('fi'), ylabel('L'), title('Stream Function')
colorbar
