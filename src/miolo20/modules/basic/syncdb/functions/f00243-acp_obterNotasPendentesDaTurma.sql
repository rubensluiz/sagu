CREATE OR REPLACE FUNCTION acp_obternotaspendentesdaturma(p_ofertaturmaid int)
RETURNS TABLE(ofertacomponentecurricularid int, disciplina varchar(255), personid bigint, personname varchar(255), professorid bigint, professorname varchar(255), email varchar(255), descricaonota VARCHAR(255)) AS
$BODY$
/******************************************************************************
  NAME: acp_obternotaspendentesdaturma
  DESCRIPTION: Obtem notas pendentes de cada turma e informações do professor

  REVISIONS:
  Ver       Date       Author             Description
  --------- ---------- ------------------ ------------------------------------
  1.0       21/10/14   Felipe Ferreira         Função criada.
******************************************************************************/
DECLARE
    v_ofertacomponentecurricularid int;
    v_ofertacomponentecurricular acpofertacomponentecurricular; --Oferta componente curricular
	
BEGIN
    FOR v_ofertacomponentecurricular IN SELECT * FROM acpofertacomponentecurricular WHERE ofertaturmaid = p_ofertaturmaid
    LOOP
	RETURN QUERY SELECT * FROM acp_obternotaspendentes(v_ofertacomponentecurricular.ofertacomponentecurricularid);
    END LOOP;

END;
$BODY$
LANGUAGE plpgsql;
