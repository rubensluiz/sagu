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
 * @author Moises Heberle [moises@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers \n
 * Eduardo Bonfandini [eduardo@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Luiz Gregory Filho [luiz@solis.coop.br]
 * Moises Heberle [moises@solis.coop.br]
 *
 * @since
 * Class created on 07/08/2008
 *
 **/


/**
 * Grid used by form to display search results
 **/
class GrdBond extends GSearchGrid
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
            new MGridColumn(_M('Código da pessoa', $this->module),     MGrid::ALIGN_RIGHT, null, null, true, null, true),
            new MGridColumn(_M('Pessoa', $this->module),          MGrid::ALIGN_LEFT,  null, null, true,  null, true),
            new MGridColumn(_M('Código do vínculo', $this->module),       MGrid::ALIGN_RIGHT, null, null, false, null, true),
            new MGridColumn(_M('Código do vínculo', $this->module),       MGrid::ALIGN_RIGHT,  null, null, true,  null, true),
            new MGridColumn(_M('Vínculo', $this->module),            MGrid::ALIGN_LEFT,  null, null, true,  null, true),
            new MGridColumn(_M('Data de validade', $this->module),   MGrid::ALIGN_RIGHT, null, null, true,  null, true, MSort::MASK_DATE_BR)
        );

        parent::__construct($data, $columns);

       //Make update action
        $args = array(
            'function' => 'update',
            'personId' => '%0%',
            'linkId'   => '%2%',
            'oldDateValidate' => '%5%'
        );
        $hrefUpdate = $this->MIOLO->getActionURL($this->module, $this->action, null, $args);

        //Make delete action
        $args = array(
            'function' => 'delete',
            'personId' => '%0%',
            'linkId'   => '%2%',
            'oldDateValidate' => '%5%'
        );

        $this->addActionUpdate( $hrefUpdate );
        $this->addActionDelete( GUtil::getAjax('tbBtnDelete_click', $args) );
        $this->setRowMethod($this, 'checkRow');
        $this->setIsScrollable();
        
    }


    function checkRow($i, $row, $actions, $columns)
    {
    	$date = new GDate($columns[5]->control[$i]->value);
        $columns[5]->control[$i]->setValue( $date->generate() );
    }

    /**
     * Este generate é especifico para a grid de vinculos, porque os itens que
     * vão ser excluídos precisam ser encontrados manualmente na grid.
     *
     * @return string
     */

    public function generate()
    {
        $this->setPrimaryKey(array('personId'=> '0', 'linkId'=>'2', 'oldDateValidate'=>'5' )); //Define primarykeys com indices apontando para as colunas da grid especificas para este caso.

        return parent::generate();
    }
}
?>
