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
 * Handler do formul�rio para visualiza��o do calend�rio acad�mico do curso
 *
 * @author Jonas Guilherme Dahmer [jonas@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Jonas Guilherme Dahmer [jonas@solis.coop.br]
 *
 * @since
 * Class created on 06/01/2012
 */

$MIOLO->checkAccess('BASIC', A_ACCESS, true, true);

if($_GET['function']=='download')
{
    $file = $MIOLO->getConf('home.modules') . '/' .$_GET['modulo'].'/html/files/reports/'.$_GET['report'].'.jrxml';
    if(!file_exists($file))
        $file = $MIOLO->getConf('home.modules') . '/' .$_GET['modulo'].'/reports/'.$_GET['report'].'.jrxml';
    
    header('Content-Description: File Transfer');
    header('Content-Type: application/rss+xml');
    header('Content-Disposition: attachment; filename='.basename($file));
    header('Content-Length: ' . filesize($file));
    ob_clean();
    flush();
    readfile($file);
    exit;
}

$module = SAGU::getFileModule(__FILE__);
$action = MIOLO::getCurrentAction();
$title = _M('Gerenciador de relat�rios', $module);
$form = 'FrmManagerReport';

SAGU::handle($module, $action, $title, $form, $form);
?>
