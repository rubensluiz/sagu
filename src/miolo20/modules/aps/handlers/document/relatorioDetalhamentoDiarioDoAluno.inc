<?php

$module = SAGU::getFileModule(__FILE__);
$action = MIOLO::getCurrentAction();
$title = _M('Relat�rio detalhamento di�rio do aluno', $module);
$form = 'FrmRelatorioDetalhamentoDiarioDoAluno';

SAGU::handle($module, $action, $title, $form, 'FrmRelatorioDetalhamentoDiarioDoAluno', array('checkAccess' => false));