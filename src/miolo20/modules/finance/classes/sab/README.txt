Manual de configura��o de boletos

Passo para configura��o de boletos
1.0 - Configura��o do banco padr�o
    1.1 - Altera��o de um banco pad�o
    1.2 - Cadastro de um banco padr�o
2.0 - Configura��o do SAB
    2.1 - Altera��o do SAB
    2.2 - Cadastro do SAB

1 - Cadastrar no m�dulo b�sico um banco padr�o para as faturas. Abaixo segue um exemplo de configura��o.

    V� at� a tabela de par�metros do m�dulo basico conforme caminho abaixo
    Home::B�sico::Configura��o::Tabela de par�metros

    No campo par�metro digite "DEFAULT_INVOICE_BANK" (sem aspas) depois precione o bot�o de localizas.
    Em caso de haver um banco cadastrado, o mesmo pode ser alterado comforme a necessidade do usu�rio (passo 1.1). Caso o banco que � utilizado pela institui��o esteje cadastrado corretamente v� para o passo 2.0.
    1.1 - Altera��o de um banco pad�o

    Para editar clique no bot�o de A��O "edit" que est� representado por uma figura de um caderno com l�pis.

    Altere o campo valor VALOR para o banco que a institui��o utiliza.
    Ap�s alterado o c�digo do banco clique no bot�o de salvar representado pela figura de um disquete.
    OBS: O valor deve ser num�rico com no m�ximo 3 caracteres. Ex: 104 ou 001 ...
    
    1.2 - Cadastro de um banco padr�o

    Para cadastrar um novo banco padr�o devemos ir no mesmo caminho do passo 1 e clicar no bot�o de novo.
    
    No campo M�DULO selecione: BASIC
    No campo PAR�MATRO digite: "DEFAULT_INVOICE_BANK" (sem aspas)
    No campo VALOR digite o c�digo do banco utilizado pela institui��o: Ex: 104
    No campo ASSINATURA sugerimos: "N�mero do banco padr�o de gera��o de t�tulos" (sem aspas)
    No campo DESCRI��O sugerimos: "N�mero do banco padr�o de gera��o de t�tulos" (sem aspas)
    No campo TIPO DE CAMPO selecione: INTEGER
    No campo VALOR PODE SER ALTERADO selecione: SIM
    
    Ap�s o preenchimento dos campos clique no bit�o de salvar representado pela figura de um disquete.
    OBS: S� pode haver um par�metro DEFAULT_INVOICE_BANK.
    
2 - Cadastrar no m�dulo b�sico o SAB. Abaixo segue um exemplo de configura��o.

    V� at� a tabela de par�metros do m�dulo basico conforme caminho abaixo
    Home::B�sico::Configura��o::Tabela de par�metros

    No campo par�metro digite "SAB_DIRECTORY" (sem aspas) depois precione o bot�o de localizas.
    Em caso de haver SAB cadastrado, o mesmo pode ser alterado comforme a necessidade do usu�rio (passo 2.1). Caso o SAB que � utilizado pela institui��o esteje cadastrado corretamente v� para o passo 3.0.

    2.1 - Altera��o do SAB

    Para editar clique no bot�o de A��O "edit" que est� representado por uma figura de um caderno com l�pis.

    Altere o campo VALOR para o caminho onde o SAB est� localizado. Ex: /usr/local/sagu/module/finance/clases/sab
    Ap�s alterado o caminho do SAB clique no bot�o de salvar representado pela figura de um disquete.
    
    2.2 - Cadastro do SAB

    Para cadastrar um novo banco padr�o devemos ir no mesmo caminho do passo 2 e clicar no bot�o de novo.
    
    No campo M�DULO selecione: BASIC
    No campo PAR�MATRO digite: "SAB_DIRECTORY" (sem aspas)
    No campo VALOR digite a localiza��o do SAB: Ex: /usr/local/sagu/modules/finance/classes/sab/
    No campo ASSINATURA sugerimos: "Caminho absoluto para sistema de boletos" (sem aspas)
    No campo DESCRI��O sugerimos: "Caminho absoluto para diret�rio do sistema de boletos" (sem aspas)
    No campo TIPO DE CAMPO selecione: VARCHAR
    No campo VALOR PODE SER ALTERADO selecione: SIM
    
    Ap�s o preenchimento dos campos clique no bot�o de salvar representado pela figura de um disquete.
    OBS: S� pode haver um par�metro SAB_DIRECTORY.
