<?php

$module = SAGU::getFileModule(__FILE__);
$action = MIOLO::getCurrentAction();
$title = _M('Frequ�ncia individual do residente na oferta de atividade do m�dulo', $module);
$form = 'FrmFrequenciaIndividualDoResidenteAtividadeDoModulo';

SAGU::handle($module, $action, $title, $form, 'FrmFrequenciaIndividualDoResidenteAtividadeDoModulo', array('checkAccess' => false));
?>