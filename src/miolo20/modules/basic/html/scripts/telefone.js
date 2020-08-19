// Obtido de http://wbruno.com.br/2012/08/02/mascara-campo-de-telefone-em-javascript-com-regex-nono-digito-telefones-sao-paulo/

/* M�scaras ER */
function mascara(o,f){
    v_obj=o
    v_fun=f
    setTimeout("execmascara()",1)
}
function execmascara(){
    v_obj.value=v_fun(v_obj.value)
}
function mtel(v){
    if ( v.length > 15 )
    {
        return v.substring(0, (v.length - 1));
    }
    
    v=v.replace(/\D/g,"");             //Remove tudo o que n�o � d�gito
    v=v.replace(/^(\d{2})(\d)/g,"($1) $2"); //Coloca par�nteses em volta dos dois primeiros d�gitos
    v=v.replace(/(\d)(\d{4})$/,"$1-$2");    //Coloca h�fen entre o quarto e o quinto d�gitos
    
    return v;
}