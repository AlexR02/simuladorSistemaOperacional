# simuladorSistemaOperacional
  

## Compilação


Para compilar o programa basta utilizar os seguintes comandos:

``make clean`` para limpar a pasta build;
``make`` para compilar o projeto;
``make run`` para rodar o projeto.

Com isso as estruturas já serão iniciadas de acordo com os dados passados no settings.json.

## Carregando os processos

Após estar com o programa rodando basta utilizar o comando ``load`` que os processos serão carregados automaticamente. Contanto que a estrutura do arquivo processos.json seja mantida, os seus valores poderão ser alterados arbitrariamente contanto que os mesmo respeitem os tipos já atribuidos. Ao tentar aplicar a utilização de threads foram encontrados diversos conflitos, porém continuaremos evoluindo o repositório para que seja possível utilizá-las. Após os processos terem sidos carregados basta utilizar o comando ``execute`` para iniciar o escalonamento. Lembrando que o escalonador pode ser trocado no arquivo settings.json, podendo utilizar as opções "FIFO", "LRU" e "MFP".
