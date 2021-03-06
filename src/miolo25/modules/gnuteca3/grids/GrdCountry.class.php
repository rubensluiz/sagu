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
 *
 * Grid
 *
 * @author Jonas C. Rosa [jonas_rosa@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers \n
 * Eduardo Bonfandini [eduardo@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * ]
 *
 * @since
 * Class created on 11/07/2012
 *
 * */
class GrdCountry extends GSearchGrid
{

    public $MIOLO;
    public $module;
    public $action;

    public function __construct($data)
    {
        $columns = array(
            new MGridColumn(_M('Código', $this->module), MGrid::ALIGN_LEFT, null, null, true, null, true),
            new MGridColumn(_M('Nome', $this->module), MGrid::ALIGN_LEFT, null, null, true, null, true),
            new MGridColumn(_M('Nacionalidade', $this->module), MGrid::ALIGN_LEFT, null, null, true, null, true),
            new MGridColumn(_M('Moeda', $this->module), MGrid::ALIGN_LEFT, null, null, true, null, true),
            new MGridColumn(_M('Moeda no plural', $this->module), MGrid::ALIGN_LEFT, null, null, true, null, true),
            new MGridColumn(_M('Descrição decimal', $this->module), MGrid::ALIGN_LEFT, null, null, true, null, true),
            new MGridColumn(_M('Descrição decimal no plural', $this->module), MGrid::ALIGN_LEFT, null, null, true, null, true),
            new MGridColumn(_M('Simbolo monetário', $this->module), MGrid::ALIGN_LEFT, null, null, true, null, true)
        );

        parent::__construct($data, $columns);

        $args = array('function' => 'update', 'countryId' => '%0%');
        $this->setIsScrollable();
        $this->addActionUpdate($this->MIOLO->getActionURL($this->module, $this->action, null, $args));
        $args = array('function' => 'delete', 'countryId' => '%0%');
        $this->addActionDelete(GUtil::getAjax('tbBtnDelete_click', $args));
    }

}

?>