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
 * Pupil frequency handler.
 * Used to allow the professor to register the frequencies for the specified group
 *
 * @author Armando Taffarel Neto [taffarel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Moises Heberle [moises@solis.coop.br]
 * Fabiano Tomasini [fabiano@solis.coop.br]
 *
 * @since
 * Class created on 10/09/2007
 *
 **/
$function = MIOLO::_request('function');

$home = 'main:process:frequency';
$navbar->addOption(_M('Registro de frequ�ncia', $module), $module, $home, null, array('function' => 'resetStack'));

$form = 'FrmFrequency';

$ui = $MIOLO->getUI();

// Verifica se tem a permiss�o 'Digita��o de notas e frequ�ncia'. Se n�o tiver, verifica a 'Registro de frequ�ncia'. Ticket #34507.
if ( !$MIOLO->checkAccess('FrmGradesTyping', A_ACCESS) )
{
    $MIOLO->checkAccess($form, A_ACCESS, true, true);
}
$content = $ui->getForm($module, $form);
$content->setClose($MIOLO->getActionURL($module, substr($action, 0, strrpos($action, ':'))));

if ( $theme->page->generateMethod != 'generateAJAX' )
{
    $theme->clearContent();
    $theme->insertContent($content);
}
?>