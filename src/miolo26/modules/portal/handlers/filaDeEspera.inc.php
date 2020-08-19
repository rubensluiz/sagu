<?php
/**
 * <--- Copyright 2005-2010 de Solis - Cooperativa de Soluções Livres Ltda.
 * 
 * Este arquivo é parte do programa Sagu.
 * 
 * O Sagu é um software livre; você pode redistribuí-lo e/ou modificá-lo
 * dentro dos termos da Licença Pública Geral GNU como publicada pela Fundação
 * do Software Livre (FSF); na versão 2 da Licença.
 * 
 * Este programa é distribuído na esperança que possa ser útil, mas SEM
 * NENHUMA GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO
 * ou APLICAÇÃO EM PARTICULAR. Veja a Licença Pública Geral GNU/GPL em
 * português para maiores detalhes.
 * 
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU, sob o título
 * "LICENCA.txt", junto com este programa, se não, acesse o Portal do Software
 * Público Brasileiro no endereço www.softwarepublico.gov.br ou escreva para a
 * Fundação do Software Livre (FSF) Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA --->
 * 
 * Finance entry handler.
 * Contains the menus to access entry registers
 *
 * @author Nataniel I. da Silva [nataniel@solis.coop.br]
 *
 * @version $Id$
 *
 * @since
 * Class created on 27/08/2014
 *
 **/

$theme->clearContent();

$ui = $MIOLO->getUI();
$navbar->addOption(_M('Fila de espera', $module), $module, $self);
$form = $ui->getForm($module, 'frmFilaDeEspera');
$theme->insertContent($form);

