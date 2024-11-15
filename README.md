# Калькулятор v.1
## Основа алгоритма
Данный калькулятор основан на идее синтаксического дерева. Узлы такого дерева представляют собой операции, а листья - операнды. У узлов такого дерева может быть два потомка(для бинарных операций) и один потомок(для унарных операций). Рекурсивный обход подобного дерева, позволяет вычислить результат выражения, для которого было составлено это дерево.
## v.2
У калькулятора есть [вторая версия](https://github.com/GambitG667/AL_DZ1_v2_1st_semestre), в ней реализован алгоритм обратной польской нотации.
## Построение дерева
Дерево создается по следующему алгоритму:
Входные данные: строка выражения
1. Создается корневая нода.
2. Если выражение редуцируемое(то есть может быть вычислено до числа или переменной), то нода становится листом.
3. Если выражение является пустой строкой, то нода становится листом и принимает значение 0.
4. Если выражение не редуцируемое, то удаляются внешние скобки и выражение перегибается в слабой точке. Слабой точкой назвается самый правый знак операции с самым низким приоритетом, знаки операций, которые находятся в скобках пропускаются. Например в выражении `(2+2)-(2/2)*2` точкой перегиба будет знак `-`. 
  - 4.1 Нода становится узлом и принимает значение знака операции в точке перегиба.
  - 4.2 Для ноды рекурсивным применением алгоритма создается левый и правый наследник, на вход рекурсивного вызова подается выражение слева от точки перегиба и справа от точки перегиба соответственно.
## Вычисление
Вычисление происходит следующим образом:
На вход подается Нода
1. Если нода - это лист, то возвращается его значение.
2. Если ноде - это операция, то для каждого из потомков выполняется алгоритм выполняется рекурсивно и над полученными значениями выполняется операция, результат операции возвращается.
 - 2.1 Если операция унарная, то значение, полученное левого потомка, отбрасывается. И операция выполняется от значения, полученного от правого потомка.

- *Уточнение* Если в выражении содержатся переменные, то их следует найти и определить до вычисления.

## Важные дополнения
Идея преобразовывать выражение в массив токенов, мне пришла, несколько позже, поэтому в этой реализации, выражение на всем протяжении остается в виде строки, поэтому для облегчения работы я заменяю длинные названия функций на однобуквенные обозначения.
