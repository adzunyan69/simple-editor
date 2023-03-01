# Краткое описание
Небольшая тестовая утилита, отображающая использование и создание кастомных объектов с возможностью изменения свойств без пересборки проекта (аналогия QObject и других решений)
# Сборка
Для сборки предварительно добавлял в CMake-конфиг следующие свойства:

`set(QT_DIR <qt5_dir…lib\\cmake\\Qt5>)`

`set(Qt5_DIR <qt5_dir…lib\\cmake\\Qt5>)`
# Запуск предсобранных версий
Соответствующие компилятору версии лежит в релизах в архивах build_mingw64_qt5_15_2
и builld_msvc17_qt5_15_2.
Работоспособность проверялась на Win11 x64 и Win10 x64, в комплекте с каждой
предсобранной версии лежат требуемые Qt-шные плагины и .dll, рантайм от
компилятора (для mscv предполагается наличие vcredist x64), а также тестовые
конфиги:
- objects.json
- objects_copy.json (для удобства восстановления исходного набора объектов)
- properties.json (конфиг для параметров объектов)
# Добавление набора объектов
Объекты в objects.json добавляются следующим образом:
```“object_name”: [
{
  “int_or_float_property”: val,
  “some_stringlist_property”:
  “current string”, “icon”: “image path”
} ]
```
(допускается добавлять N объектов с одним object_name в json-массив).
Добавление объектов-свойств
Шаблоны объектов / свойств в properties.json добавляются следующим образом:
```
“object_name”: {
    “int_or_float_property”: {
    “type”: “int”,
    “from”: -5,
    “to”: 5
  },
    “string list property”: {
    “type”: “array”,
    “items”: [ … ]
  },
    “icon property”: {
    “type”: “image”,
  }
}
```
# Поддерживаемые типы
- `int` / `float`. Численные свойства. Можно задавать ограничения снизу-сверху через `from` и `to`.
- `array`. Набор строковых значений, допустимых для свойства.
- `image`. Путь к файлу с изображением.
# Краткое описание структуры программы
Программа логически поделена на три модуля:
- `custom_object`: для работы с самим набором объектов
- `properties_config`: для работы с “шаблоном” объектов и их свойств
- `property_widgets`: для визуального отображения объектов на основе свойств из
конфига и их текущего значения
## CustomObject
Класс представляет собой аналогию QObject-а с его динамическим добавлением и
использованием именованных свойств.
Данная простая реализация была сделана для того, чтобы не тянуть с собой указание
родителя для каждого QObject-а и не привязываться к Qt-шному сборщику мусора, а
без родительского указателя пришлось бы либо следить за временем существования
объекта и вовремя его удалять, либо оборачиваться в smart-pointers, что, вроде, не
рекомендуется.
## Object Reader & Object Writer
Абстрактные классы (и их конкретные реализации Json…) для загрузки и сохранения
набора объектов.
Для разного способа извлечения и сохранения необходимо сделать производные
классы и использовать их как аргумент при выполнении операции над объектами.
## Object & Property Widgets
Данные виджеты представляют собой контейнеры для отображения объектов и их
свойств.
Для базовых типов приведены простые реализации gui-интерфейса с простейшей
версткой, которые используют ограничения над свойствами (если такие были указаны
в конфиге).
Для добавления своего отображения или обработки другого базового типа свойств
необходимо отнаследоваться от PropertyWidget и сделать свою реализацию.
Для упрощения кода некоторые действия были предварительно сделаны в
PropertyWidget в конструкторе. Сами потомки создаются через фабрику
PropertyWidgetsFactory.
## Property Info
Класс использует QMetaType и представляет собой аналогию std::any и QVariant с
небольшими дополнениями в виде фильтров свойства и “массивом применяемых
значений” (для массивов).
Иерархия наследования не была выбрана, т. к. это влечет за собой использование
dynamic_cast или qobject_cast с соответствующими затратами, либо использование
(как я предполагаю) паттерна visitor, что сильно усложнит код программы и добавление
новых типов в дальнейшем.
Фабрика была создана для извлечения свойств только из Json-конфига.
# Ограничения и todo
- Заложена обработка только базовых типов на основе примера в задании (int и
float с ограничениями, icon для изображений, string list для массива
строковых значений). Добавление других типов (double, string, массива других
типов и т. д.) реализуется путем реализации требуемого виджета и небольшими
доработками в других местах. Исключение,скорее всего, вложенные сложные
свойства - здесь бы пришлось предусмотреть вложенность PropertyInfo в самого
себя на основе QVariant и пользовательского типа.
- Отсутствуют gui-методы для добавления-изменения как объектов, так и типов
свойств (т. к. большую часть времени потребует формирование gui для всех
этих процедур) и в целом упрощенный интерфейс
- public -> private конструкторы для объектов, которые создаются фабриками
- Не сохраняется порядок объектов, в котором были записаны объектов (т. к. сам
QjsonDocument итерируется по ключам как в хэш-таблице), однако свойства
сортируются в алфавитном порядке, т. к. хранятся в QVariantMap.
- Небольшая обработка ошибок (точнее, информирование о них) и отсутствие
исключений (т. к. также усложнит чтение исходников).
