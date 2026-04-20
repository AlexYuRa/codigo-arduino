# Sistema de riego automatico con Arduino

Proyecto de riego automatico basado en Arduino para activar una minibomba de agua segun la humedad del suelo.

## Descripcion

Este proyecto usa un sensor de humedad para medir el nivel de humedad en la tierra. Cuando el valor baja por debajo de un umbral configurado, el Arduino activa un rele para encender una minibomba de agua sumergible.

## Componentes

- Arduino Uno o Arduino Mega
- Sensor de humedad de suelo
- Modulo rele
- Minibomba de agua sumergible
- Fuente de alimentacion adecuada para la bomba
- Cables de conexion

## Funcionamiento general

1. El sensor de humedad lee el nivel de humedad del suelo.
2. Arduino compara el valor leido con el umbral definido en el codigo.
3. Si el suelo esta seco, se activa el rele.
4. El rele enciende la minibomba para regar.
5. Cuando se alcanza la humedad esperada, se apaga la bomba.

## Archivo principal

- [car1.ino](car1.ino): logica principal del sistema.

## Carga del codigo

1. Abre [car1.ino](car1.ino) en Arduino IDE.
2. Selecciona la placa correcta (Uno o Mega) y el puerto.
3. Compila y sube el programa al Arduino.

## Seguridad y notas

- No alimentes la bomba directamente desde el pin del Arduino.
- Usa una fuente externa para la bomba y conecta GND comun cuando corresponda.
- Verifica la corriente maxima del rele y de la fuente.

## Licencia

Este proyecto se distribuye bajo licencia MIT. Revisa [LICENSE](LICENSE) para mas detalles.
