<?php

/**
 * <--- Copyright 2005-2010 de Solis - Cooperativa de Solu��es Livres Ltda.
 * 
 * Este arquivo � parte do programa Sagu.
 * 
 * O Sagu � um software livre; voc� pode redistribu�-lo e/ou modific�-lo
 * dentro dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o
 * do Software Livre (FSF); na vers�o 2 da Licen�a.
 * 
 * Este programa � distribu�do na esperan�a que possa ser �til, mas SEM
 * NENHUMA GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO
 * ou APLICA��O EM PARTICULAR. Veja a Licen�a P�blica Geral GNU/GPL em
 * portugu�s para maiores detalhes.
 * 
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU, sob o t�tulo
 * "LICENCA.txt", junto com este programa, se n�o, acesse o Portal do Software
 * P�blico Brasileiro no endere�o www.softwarepublico.gov.br ou escreva para a
 * Funda��o do Software Livre (FSF) Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA --->
 * 
 * Sagu2 coding standart documentation handler.
 * Constains script to download the coding standart document
 *
 * @author Daniel Afonso Heisler [daniel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Eduardo Beal Miglioransa [eduardo@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 22/10/2006
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$MIOLO->checkAccess("ADMIN", A_ACCESS, true, true);

$home = 'main:documentation:developer:codingStandart';
$navbar->addOption(_M('Padroniza��o de c�digo', $module), $module, $home);

$ui   = $MIOLO->getUI();
$file = MIOLO::_request('file');

//testa se o arquivo existe
if ( file_exists(SAGU::getParameter('BASIC', 'DOCUMENTATION_PATH') . '/coding_standard.pdf') )
{
    header("Cache-Control: public, must-revalidate");
    header("Content-Type: " . 'pdf');
    header("Content-Length: " .(string)(filesize(SAGU::getParameter('BASIC', 'DOCUMENTATION_PATH') . '/coding_standard.pdf')) );
    header('Content-Disposition: attachment; filename="coding_standard.pdf"');
    header("Content-Transfer-Encoding: binary\n");
    readfile(SAGU::getParameter('BASIC', 'DOCUMENTATION_PATH') . '/coding_standard.pdf');
}
else
{
    //mensgem de erro de arquivo inexistente
}

?>
