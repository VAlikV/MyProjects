function Si = N2T(n, S) % Возвращает номера элементов, содержихих указанный узел
[rows, cols] = find(S == n);
%Si = rows;
Si = sort(rows);
