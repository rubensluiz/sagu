CREATE OR REPLACE FUNCTION acp_verificaSeEstaConfirmadoNaInscricao(p_inscricaoId INT)
RETURNS BOOLEAN AS
$BODY$
BEGIN
    RETURN (
        SELECT (CASE RMPC.formadeconfirmacaoinscricao
		     WHEN 'N' --Nenhum
		     THEN
		          TRUE
		     WHEN 'T' --Pagamento da taxa de inscricao
		     THEN
		          acp_verificaSeTaxaDeInscricaoFoiPaga(I.inscricaoId)
		     WHEN 'M' --Manual
		     THEN
		          (I.situacao = 'I')
		END)
	  FROM acpInscricao I
    INNER JOIN acpOfertaCurso B
            ON (I.ofertacursoid = B.ofertacursoid)
    INNER JOIN acpOcorrenciaCurso O
            ON (O.ocorrenciacursoid = B.ocorrenciacursoid)
    INNER JOIN acpCurso A
            ON (A.cursoid = O.cursoid)
    INNER JOIN acpPerfilCurso PC
	    ON PC.perfilCursoId = A.perfilCursoId
     LEFT JOIN acpRegrasMatriculaPerfilCurso RMPC
	    ON RMPC.perfilCursoId = PC.perfilCursoId
	 WHERE I.inscricaoId = p_inscricaoId
    );
END;
$BODY$
LANGUAGE plpgsql IMMUTABLE;