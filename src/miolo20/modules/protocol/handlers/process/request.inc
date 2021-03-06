<?php
/**
 * <--- Copyright 2011-2011 de Facimed - Faculdade de Ci�ncias Biom�tricas de Cacoal.
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
 * Cont�m as solicita��es
 *
 * @author Alessandro Rodrigues da Cruz [cpd@facimed.edu.br]
 *
 * \b Maintainers: \n
 * Equipe Solis [sagu2@solis.coop.br]
 * 
 * @since
 * Class created on 19/03/2011
 *
 **/

$function = MIOLO::_REQUEST('function');
$ui = $MIOLO->getUI();

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$navbar->addOption(_M('Solicita��o', $module), $module, $action);
access::insert('Solicita��o', $action, 'default-16x16.png');

switch ( $function )
{
    case 'update':
        $MIOLO->checkAccess('ptcFrmRequest', A_ACCESS, true, true);

        $content = $ui->getForm($module,'FrmRequestEdit', $data);
    break;
    case 'delete':
        $MIOLO->checkAccess('ptcFrmRequest', A_DELETE, true, true);

        $content = $ui->getForm($module,'FrmRequestEdit', $data);
    break;
    default:
        $MIOLO->checkAccess('ptcFrmRequest', A_INSERT, true, true);

        $i=1;
        $steps[$i++] = new SStepInfo('FrmRequest',  _M('Solicita��o', $module), $module);
        $steps[$i++] = new SStepInfo('FrmDocument',  _M('Documentos', $module), $module);
        
        // verifica se deve criar o passo Informacoes adicionais, de campos personalizados
        $data = sstepbystepform::getAllStepDataStatic();
        $subjectId = $data['subjectId'];
        
        if ( strlen($subjectId) > 0 )
        {
            $customFieldIds = BasCustomField::getCustomFieldIdsBySubject($subjectId);
            
            if ( count($customFieldIds) > 0 )
            {
                $steps[$i++] = new SStepInfo('FrmInfoAdicional', _M('Informa��es adicionais', $module), $module);
            }
        }

        $content = SStepByStepForm::getCurrentForm($steps);
    break;
}

$theme->clearContent();
$theme->insertContent($content);
?>