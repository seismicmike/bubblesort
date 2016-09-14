<?php

/**
 * @file
 * Admin configuration for bubblesort.
 */

/**
 * Bubblesort config form.
 */
function bubblesort_simulator_config($form, &$form_state) {
  $form['bubblesort_array_size'] = [
    '#title' => t('Size of the array to sort'),
    '#type' => 'textfield',
    '#size' => 5,
    '#description' => t('Please enter a number of values to sort, from 2 to 20'),
    '#element_validate' => ['bubblesort_validate_array_size'],
    '#required' => TRUE,
    '#default_value' => bubblesort_get_array_size(),
  ];

  $form['range'] = [
    '#type' => 'fieldset',
    '#title' => t('Sort Range'),
    '#description' => t('Sort values in this range'),
    '#collapsible' => FALSE,
    '#tree' => FALSE,
  ];

  $form['range']['bubblesort_range_min'] = [
    '#title' => t('Range Minimum'),
  ];

  $form['bubblesort_sort_direction'] = [
    '#title' => t('Sort direction for the bubblesort algorithm'),
    '#type' => 'select',
    '#options' => [
      'descending' => 'Descending - Larger to the top.',
      'ascending' => 'Ascending - Smaller to the top.',
    ],
    '#default_value' => bubblesort_get_sort_direction(),
  ];

  return system_settings_form($form);
}
