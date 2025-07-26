# Simulador de Scalextric con la API Vulkan

Este proyecto es un simulador 3D del clásico juego Scalextric, desarrollado desde cero utilizando la API gráfica de bajo nivel **Vulkan**. El objetivo principal ha sido reproducir la esencia del Scalextric físico en un entorno digital interactivo, con un enfoque centrado tanto en la fidelidad gráfica como en la física básica del juego.

## Índice

- [Objetivos](#-objetivos)
- [Características](#-características)
- [Modelado y gráficos](#-modelado-y-gráficos)
- [Coches](#-coches)
- [Circuitos](#-circuitos)
- [Controles y ejecución](#-controles-y-ejecución)
- [Estructura del repositorio](#-estructura-del-repositorio)
- [Requisitos y ejecución](#️-requisitos-y-ejecución)
- [Mejoras futuras](#-mejoras-futuras)
- [Licencia](#-licencia)

---

## Objetivos

- Desarrollar una aplicación gráfica de bajo nivel utilizando Vulkan como tecnología base.
- Modelar pistas tridimensionales (rectas, curvas, cambio de carril) y ensamblarlas en circuitos.
- Importar modelos 3D de coches en formato OBJ y adaptarlos a Vulkan.
- Simular la jugabilidad básica del Scalextric: velocidad, cambio de carril, colisiones, salidas de pista.
- Diseñar un entorno gráfico completo con Skybox, iluminación, y HUD informativo.
- Profundizar en técnicas gráficas avanzadas sin motores de alto nivel.

---

## Características

- API Vulkan implementada desde cero.
- Modelado manual de pistas y circuitos.
- Importación y adaptación de modelos OBJ y MTL.
- Detección de colisiones y salidas de pista.
- Skybox envolvente mediante CubeMap.
- HUD con cronómetro, número de vueltas, estado del coche y eventos visuales.

---

## Modelado y gráficos

- Tipos de pista: rectas, curvas, cambio de carril, pista de conexión, arco de meta.
- Texturizado manual ajustado a cada geometría.
- Mallas triangulares para compatibilidad con el pipeline de Vulkan.
- Iluminación basada en el modelo Phong.
- Skybox generado con 6 imágenes para una ambientación realista.

---

## Coches

- 12 coches de Fórmula 1 (temporada 2011).
- Modelos `.obj` + `.mtl` importados mediante un parser adaptado.
- Cada coche está compuesto por piezas (`CAPiece`) organizadas en `CAObject`.

---

## Circuitos

- Circuitos reales adaptados del blog [Mis circuitos de slot](http://miscircuitosdeslot.blogspot.com.es).
- Cada circuito implementado como clase hija de `CACircuito`.
- Las pistas se colocan de forma secuencial con transformaciones acumulativas.
- Tipos de curva: interior, estándar, exterior, super exterior (izquierda/derecha).

---

## Controles y ejecución

### Argumentos de ejecución

La aplicación se ejecuta desde el archivo **`TFG.exe`** ubicado en `x64/Release/`, y admite los siguientes argumentos opcionales:

```bash
TFG.exe -circuitN -carM -carX -timeZ
```

Donde:

- `-circuitN`: Especifica el circuito a cargar.
- `-carM`: Indica el coche del primer jugador.
- `-carX`: Indica el coche del segundo jugador.
- `-timeZ`: Duración de la partida (en segundos).

### 🏁 Circuitos disponibles

| Argumento       | Clase cargada           |
|------------------|--------------------------|
| `-circuit1`      | `CACircuito_1`           |
| `-circuit2`      | `CACircuito_2`           |
| `-circuit3`      | `CACircuito_3`           |
| `-circuit4`      | `CACircuito_4`           |
| `-circuit293`    | `CACircuito_293`         |
| `-circuit380`    | `CACircuito_380`         |
| `-circuit946`    | `CACircuito_946`         |
| `-circuit999`    | `CACircuito_jerez`       |

> Por defecto: `CACircuito_1`

### 🚗 Coches disponibles

| Argumento   | Clase cargada     |
|-------------|--------------------|
| `-car1`     | `CAForceIndia`     |
| `-car2`     | `CAMercedes`       |
| `-car3`     | `CARedbull`        |
| `-car4`     | `CATororosso`      |
| `-car5`     | `CAWilliams`       |
| `-car6`     | `CAMclaren`        |
| `-car7`     | `CARenault`        |
| `-car8`     | `CAVirgin`         |
| `-car9`     | `CAHrt`            |
| `-car10`    | `CALotus`          |
| `-car11`    | `CASauber`         |
| `-car12`    | `CAFerrari`        |

> Por defecto:
> - Primer coche: `CAFerrari`
> - Segundo coche: `CATororosso`

### Duración de la partida

- `-timeZ`: Define la duración total de la partida en segundos.
- Por defecto: `120` segundos (2 minutos)

### Ejemplo

```bash
x64/Release/TFG.exe -circuit380 -car3 -car8 -time180
```

---

## Estructura del repositorio

```plaintext
📁 TFG/Clases_coches/        # Clases y geometría de los coches importados
📁 TFG/Clases_Circuito/      # Definición y configuración de circuitos
📁 TFG/texturas/             # Gestión de texturas, etiquetas, HUD
📁 TFG/shaders/              # Shaders de Vulkan para geometría y skybox
📄 TFG/main.cpp              # Función principal
📁 x64/
    └── 📁 Release/          # Carpeta que contiene el ejecutable final
        └── TFG.exe           # Ejecutable principal del proyecto
📄 README.md                 # Este archivo
```

---
### Teclas disponibles

- `↑` / `W`: Aumentar velocidad
- `↓` / `S`: Reducir velocidad
- `←` / `A`: Solicitar cambio de carril
- `→` / `D`: Cancelar petición de cambio de carril
- `ESP`: Cambiar de coche


## Requisitos y ejecución

### Requisitos

- Windows 10/11
- Vulkan SDK instalado
- Tarjeta gráfica compatible con Vulkan
- Compilador C++17 (GCC, MSVC, Clang)

### Ejecución

```bash
x64/Release/TFG.exe [argumentos]
```

---

## Mejoras futuras

- Menú interactivo para selección de coches y circuitos
- Sombras dinámicas y teselado de terreno
- Soporte para audio y música
- Animaciones (como ruedas girando)
- Compatibilidad con servidores para multijugador local
- Variabilidad en altura de pistas (pendientes)

---

## Licencia

Este simulador ha sido desarrollado como Trabajo Fin de Grado por **Uadad Sidelgaum Limam**, bajo la tutoría de **Francisco José Moreno Velo**, en la **Universidad de Huelva**.
