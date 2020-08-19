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
 * @author Nataniel I. da Silva [nataniel@solis.coop.br]
 *
 * @version: $Id$
 *
 * @since
 * Class created on 09/06/2015
 *
 **/

class frmSearchAvaCategoria extends ASearchForm
{
    /**
     * Construtor do formulário.
     */
    public function __construct()
    {
        $this->target = 'avaCategoria';
        parent::__construct('Buscar categorias');
    }

    /**
     * Criar os campos do formulário.
     */
    public function createFields()
    {
        $MIOLO = MIOLO::getInstance();
        $module = MIOLO::getCurrentModule();
        
        parent::createFields();
        
        $fields[] = new MIntegerField('categoriaId', '', 'Código', 10);
        $fields[] = new MTextField('descricao', '', 'Descrição', 60);
        $fields[] = new MTextField('tipo', '', 'Tipo', 60);
        $fields[] = $this->getButtons();
        
        $this->grid = $this->manager->getUI()->getGrid($module, 'grdSearchAvaCategoria');
        $this->grid->setData($this->searchButton_click((Object)array('return'=>true)));
        $fields[] = new MDiv('divGrid', $this->grid->generate());
        
        $this->addFields($fields);
    }

    /**
     * Ação do botão limpar.
     */
    public function clearButton_click()
    {
        $this->getField('categoriaId')->setValue('');
        $this->getField('descricao')->setValue('');
        $this->getField('tipo')->setValue('');
    }
}