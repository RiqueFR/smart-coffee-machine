# smart-coffee-machine

Esse projeto consiste na adaptação de uma cafeteira comum, em uma cafeteira smart, usando um microcontrolador ESP32, sensores e conexão com o [Home Assistant](https://www.home-assistant.io/), por meio do sistema [ESPHome](https://esphome.io/),
que permite a automatização dela com outros dispositivos, como por exemplo a Alexa.</br>
É possível assistir a demonstração e explicação do projeto por meio do seguinte vídeo:
[![Vídeo apresentação cafeteira](https://img.youtube.com/vi/JX29TkHWjt0/0.jpg)](https://www.youtube.com/watch?v=JX29TkHWjt0)

Esse projeto usa as ferramentas/plataformas:
- PlatformIO
- Home Assistant
- ESPHome
- Node-RED
- Alexa

## Features

- Escolher a quantidade de café por meio do número de xícaras
- Interface na cafeteira (botões para escolher a quantidade de xícaras, display para exibir a quantidade e o status)
- Conexão com o Home Assistant
- Por meio da conexão com o Home Assistant é possível integrar a cafeteira com diversos outro serviços, como por exemplo comandos de voz da Alexa
- Enchimento automático do reservatório de água da cafeteira
- Sensor para não ser ativada sem uma xícara

## Usage

Para usar esse projeto, você precisa de pelo menos o ESPHome instalado, para que seja possível passar o código para o microcontrolador, basta colocar o projeto na pasta do ESPHome, e usar as ferramentas da plataforma para subir o código.</br>
Existe a versão do código na branch "main" que não necessita do ESPHome, porém ela é desprovida de qualquer conexão com o Home Assistant ou Alexa.</br>

O projeto foi feito com o intuito de ser apresentado na amostra de projetos da disciplina de Projeto Integrado de Computação 2 da UFES, portanto alguns detalhes foram pensados para isso, e caso venha a ser reproduzido para uso pessoal, devem ser abordados outros métodos.</br>
Portanto, até existe um esquemático do projeto na branch "schematic", mas ele deve ser alterado para o seu uso, e apenas usado como base.</br>

O projeto foi calibrado para uso com a cafeteira que tínhamos acesso, portanto ele deve ser recalibrado para outras cafeteiras, isso pode ser feito colocando xícaras de café cheias de água no reservatório da cafeteira e observar as diferenças de distância lidas pelo sensor de ultrassom para cada xícara,
esse valor deve ser setado na variável apropriada.</br>

Para apresentar o projeto na amostra, foi usado uma pequena bomba de água para encher o reservatório, o que não é prático caso o projeto seja feito para uso, o melhor seria usar uma válvula que libera ou bloqueia a passagem de água, e que esteja ligada a tubulação,
para que o enchimento seja feito de maneira totalmente automática.</br>

A branch configs possui configurações das conexões/ferrantas usadas pelo projeto, arquivos de configuração do Home Assistant, Node-RED e ESPHome. Os arquivos de configuração do ESPHome estão desatualizados, o arquivo correto de configuração é o que está
presente nesta branch, o "esp32.yaml".

## TO-DO

- Melhorar documentação
- Modularizar mais o código para que as configurações possam ser feitas na interface do ESPHome (como número de xícaras)
- Criar um modo de calibração, para que seja possível usar com todas cafeteiras
- Criar um esquemático geral, que seja fácil de ser reproduzido para todos os projetos.
