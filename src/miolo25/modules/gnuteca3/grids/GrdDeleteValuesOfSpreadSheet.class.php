<?php
/**
 * <--- Copyright 2005-2011 de Solis - Cooperativa de Soluções Livres Ltda. e
 * Univates - Centro Universitário.
 * 
 * Este arquivo é parte do programa Gnuteca.
 * 
 * O Gnuteca é um software livre; você pode redistribuí-lo e/ou modificá-lo
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
 * Grid
 *
 * @author Jader Osvino Fiegenbaum [jader@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers \n
 * Jader Osvino Fiegenbaum [jader@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 *
 * @since
 * Class created on 26/11/2010
 *
 **/


/**
 * Grid used by form to display search results
 **/
class GrdDeleteValuesOfSpreadSheet extends GGrid
{
    public $MIOLO;
    public $module;
    public $action;


    public function __construct($data)
    {
        $this->MIOLO  = MIOLO::getInstance();
        $this->module = MIOLO::getCurrentModule();
        $this->action = MIOLO::getCurrentAction();

        $columns = array(
            new MGridColumn(_M('Categoria', $this->module), MGrid::ALIGN_CENTER, null, null, true, null, true),
            new MGridColumn(_M('Nível',     $this->module), MGrid::ALIGN_CENTER, null, null, true, null, true),
            new MGridColumn(_M('Campo',     $this->module), MGrid::ALIGN_CENTER, null, null, true, null, true),
            new MGridColumn(_M('Subcampo',     $this->module), MGrid::ALIGN_CENTER, null, null, true, null, true),
            new MGridColumn(_M('Registros', $this->module), MGrid::ALIGN_LEFT,   null, null, true, null, true)
        );

        parent::__construct($data, $columns, $this->MIOLO->getCurrentURL(), 0, 0, 'gridDeleteValuesOfSpreadSheet');

        $this->setIsScrollable();
        
    }
}
?>
