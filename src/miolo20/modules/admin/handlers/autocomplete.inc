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
 *
 * This file autocomplete
 *
 * @author Leovan Tavares da Silva [leovan] [leovan@solis.coop.br]
 *
 * $version: $Id$
 *
 * \b Maintainers \n
 * Thomas Spriestersbach [author] [ts@interact2000.com.br]
 * Vilson Cristiano Gartner [author] [vgartner@univates.br]
 * Thomas Spriestersbach [ts@interact2000.com.br]
 * Vilson Cristiano Gartner [vgartner@univates.br]
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Leovan Tavares da Silva [leovan@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 * 
 * @since
 * Class created on 14/10/2004
 *
 **/

$MIOLO->history->pop();

$module  = MIOLO::_Request('lmodule');
$item    = MIOLO::_Request('item');
$related = MIOLO::_Request('related');
$form    = MIOLO::_Request('form');
$field   = MIOLO::_Request('field');
$value   = MIOLO::_Request('value');

$MIOLO = MIOLO::getInstance();
$MIOLO->conf->loadConf($module);
$autocomplete = new MAutoComplete($module,$item,$value,$defaults);

$page->AddScript('m_lookup.js');

$info = $autocomplete->getResult();
if(is_array($info))
{
    $inf = 'var info = new Array();';
    foreach($info as $n=>$i)
    {
        $inf .= "\ninfo[$n] = '".addslashes($i)."';";
    }
    $info = implode(',',$info);
}
else
{
    $inf = 'var info = \''.addslashes($info).'\';';
}

header ("Cache-Control: no-cache, must-revalidate");  // HTTP/1.1
header ("Pragma: no-cache");                          // HTTP/1.0

$content =  "<html>\n";
$content .=  "<body>\n";
$content .=  "        Module=$module; Item=$item; Value=$value; Info=" . $info . "<br>\n";
$content .=  "<script language=\"JavaScript\">;\n";
$content .=  "doc  = top.frames['content'] ? top.frames['content'].document : top.document;";
$content .=  "form = doc.getElementsByName('$form')[0]; ";
$content .=  " var debugMessage=''; ";
$msg = "[autocomplete]: Field @1 not found!<br />";

    //$content .=  "\nif(form['{$r}_sel'])\n\tform['{$r}_sel'].value = '{$info[$i]}';";
    //$content .=  "\nif(form['$r'])\n\tform['$r'].value = '{$info[$i++]}';";
if(MUtil::getBooleanValue($MIOLO->getConf('options.debug')) && $MIOLO->getConf('logs.handler') == 'screen')
{
    $content .=  " \ndebugMessage = '"._M($msg,$module)."';";
}
$content .=  $inf;
$content .=  "MIOLO_AutoCompleteDeliver(doc, form, debugMessage, '$related', info);";
$content .=  "</script>\n";
$content .=  "</body>\n";
$content .=  "</html>";
$page->generate();
echo $content;
exit;

?>

