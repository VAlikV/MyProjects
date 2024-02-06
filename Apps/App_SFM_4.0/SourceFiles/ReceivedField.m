function [Bz, DES] = ReceivedField(I, K, N, S, Node, ROI, Bdes) % Расчет и отрисовка полученного поля

Bz = zeros(K,1);
Temp = 0;
for j = 1:N
    b = Calcbz(j, S, Node, ROI);
    Temp = Temp + I(j,1)*b;
end
Bz(:,1) = Temp;

DES = Bdes - Bz;
