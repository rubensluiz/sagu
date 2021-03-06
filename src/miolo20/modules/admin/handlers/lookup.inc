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
 * This file lookup
 *
 * @author Leovan Tavares da Silva [leovan] [leovan@solis.coop.br]
 *
 * $version: $Id$
 *
 * \b Maintainers \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Leovan Tavares da Silva [leovan@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 * 
 * @since
 * Class created on 14/06/2006
 *
 **/
 
$MIOLO->history->pop();
$lookup = new MLookup();

$text   = MIOLO::_Request('selText');
if ( $text && $text != 'undefined')
{
    $lookup->setSelectionText( $text );
}
$MIOLO->conf->loadConf( $lookup->module );
$MIOLO->getTheme( $MIOLO->GetConf('theme.lookup') );

$file = $MIOLO->GetModulePath($lookup->module,'db/lookup.class');
if ( file_exists( $file ) )
{
   $ok = $MIOLO->Uses('/db/lookup.class',$lookup->module);
}
else
{
   $ok = $MIOLO->Uses('/classes/lookup.class',$lookup->module);
}
$MIOLO->Assert($ok,_M('Arquivo modules/@1/classes/lookup.class n�o encontrado.', 'admin') . '<br/>' .
                   _M('Este arquivo deve implementar a classe Business@1Lookup', 'admin', $lookup->module) .
                   _M('contendo o m�todo Lookup@1.','admin', $lookup->item) );
$page->AddScript('m_lookup.js');
$page->SetTitle(_M('Janela de busca','admin'));
$businessClass = "Business{$lookup->module}Lookup";
$lookupMethod = "Lookup{$lookup->item}";

//Carregar autoload
require_once $MIOLO->getConf('home.modules') . '/modules.inc';

$object = new $businessClass();
$object->$lookupMethod($lookup);
$page->SetAction($lookup->href);

$theme = $MIOLO->GetTheme($MIOLO->GetConf('theme.lookup'),'lookup');
$theme->SetContent($lookup->generate( ));
$theme->SetLayout('lookup');
?>

