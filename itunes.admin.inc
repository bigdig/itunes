<?php
// $Id$

/**
 * Settings form.
 */
function itunes_admin_settings() {
  $types = array();
  foreach (node_get_types() as $type) {
    $types[$type->type] = $type->name;
  }
  $form['itunes_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node types'),
    '#options' => $types,
    '#default_value' => variable_get('itunes_types', array('audio')),
    '#description' => t('Associate iTunes feed item information with node types.'),
  );
  $form['#validate'][] = 'itunes_admin_settings_validate';

  return system_settings_form($form);
}

function itunes_admin_settings_validate($form, &$form_state) {
  // Retrieve selected types - Forms API sets the value of unselected checkboxes to 0.
  $form_state['values']['itunes_types'] = array_keys(array_filter($form_state['values']['itunes_types']));
}