<?php
// $Id$

/**
 * Settings form.
 */
function itunes_admin_settings() {
  $node_types = node_get_types();

  // Build a list of node types that iTunes could operate on.
  $options = array();
  foreach ($node_types as $type) {
    $options[$type->type] = $type->name;
  }
  $form['itunes_types'] = array(
    '#title' => t('Enable iTunes fields'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => variable_get('itunes_types', array('audio')),
  );

  // If FileField is enabled then let them select the enclosure field.
  if (module_exists('content') && module_exists('filefield')) {
    $fields = variable_get('itunes_filefields', array());
    $form['itunes_filefields'] = array(
      '#tree' => TRUE,
    );
    // Build the node's filefield selector.
    foreach ($node_types as $type) {
      $content = content_types($type->type);
      $options = array(NULL => t('- None -'));
      foreach ($content['fields'] as $field_name => $field) {
        if ($field['type'] == 'filefield') {
          $options[$field_name] = $field['widget']['label'];
        }
      }
      $form['itunes_filefields'][$type->type] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => empty($fields[$type->type]) ? NULL : $fields[$type->type],
        '#access' => count($options) > 1,
      );
    }
  }

  $form = system_settings_form($form);
  $form['#validate'][] = 'itunes_admin_settings_validate';
  $form['#theme'] = 'itunes_admin_settings';
  return $form;
}

function itunes_admin_settings_validate($form, &$form_state) {
  // Retrieve selected types - Forms API sets the value of unselected checkboxes to 0.
  $form_state['values']['itunes_types'] = array_keys(array_filter($form_state['values']['itunes_types']));
}

function theme_itunes_admin_settings($form) {
  $rows = array();
  $header = array($form['itunes_types']['#title']);
  unset($form['itunes_types']['#title']);

  $has_filefields = FALSE;
  foreach (element_children($form['itunes_types']) as $key) {
    $row = array(drupal_render($form['itunes_types'][$key]));
    if (isset($form['itunes_filefields'][$key])) {
      $row[] = drupal_render($form['itunes_filefields'][$key]);
      $has_filefields = TRUE;
    }
    $rows[] = $row;
  }

  if ($has_filefields) {
    $header[] = t('FileField to list in RSS feeds');
  }

  return theme('table', $header, $rows) . drupal_render($form);
}