<?php

$module = SAGU::getFileModule(__FILE__);
$action = MIOLO::getCurrentAction();
$title = _M('Relat�rio de notas do residente', $module);
$form = 'FrmRelatorioNotasIndividualDoResidente';

SAGU::handle($module, $action, $title, $form, 'FrmRelatorioNotasIndividualDoResidente', array('checkAccess' => false));