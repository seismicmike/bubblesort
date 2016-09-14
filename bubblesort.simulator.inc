<?php

/**
 * @file
 * Main UI for the Bubblesort Simulator.
 */

/**
 * Simulator form.
 */
function bubblesort_simulator($form, &$form_state) {
  $form['markup'] = [
    '#markup' => '<p>Welcome to the Bubblesort Simulator. To begin, click the Shuffle button below to initialize the table, and then click the Step button to watch the data get shuffled.</p>',
  ];

  if (isset($form_state['array'])) {
    $form['bubblesort'] = [
      '#markup' => theme('bubblesort_table', $form_state),
    ];
  }

  $form['actions']['shuffle'] = [
    '#type' => 'submit',
    '#value' => t('Shuffle'),
  ];

  /*
   * Show the Step button if
   * - The array has been initialize (shuffled).
   * - The array is not yet sorted.
   */
  if (isset($form_state['array']) && !empty($form_state['array']) && !bubblesort_is_array_sorted($form_state['array'])) {
    $form['actions']['step'] = [
      '#type' => 'submit',
      '#value' => t('Step'),
    ];
  }

  return $form;
}

/**
 * Submit handler for the bubble sort form.
 */
function bubblesort_simulator_submit(&$form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  // Load or generate the form state array.
  if ($form_state['values']['op'] === 'Shuffle') {
    $form_state['array'] = bubblesort_generate_array();
    unset($form_state['i']);
    unset($form_state['j']);
    unset($form_state['comparison_key']);
  }

  if ($form_state['values']['op'] === 'Step') {
    /*
     * Normally a bubble sort algorithm takes the form of two nested for
     * loops, like so:
     *
     * $size = count($array);
     *
     * for ($i = 0; $i < $size; $i++) {
     *   for ($j = 0; $j < $size; $j++) {
     *     if ($array[$j + 1] > $array[$j]) {
     *       list($array[$j], $array[$j + 1]) = array(
     *         $array[$j + 1],
     *         $array[$j]
     *       );
     *     }
     *   }
     * }
     *
     * However, I had to structure this rather differencly to enable stepping
     * through the algorithm. In this case, I stored the counters $i and $j in
     * the form state. Here I initialize them at the start of the algorithm,
     * or load them if the algorithm is already in progress.
     */
    $i = isset($form_state['i']) ? $form_state['i'] : 0;
    $j = isset($form_state['j']) ? $form_state['j'] : 0;
    $size = count($form_state['array']);

    // This simulates reaching the end of the internal for loop, incrementing
    // the index of the outer for loop and resetting the inner for loop index
    // to 0 so that it can run again for the next iteration.
    if ($j === $size - 1 - $i) {
      $i++;
      $j = 0;
    }

    // In order to highlight the row that we're comparing accurately, and not
    // get off track when a swap is made, store the current $j index.
    $form_state['comparison_key'] = $j;

    // This comparison supports both Ascending and Descending sorts.
    // Ascending will push the largest item to the bottom of the array, then \
    // the next lagest next to it, and so forth until it's sorted with the
    // smallest at the top.
    //
    // Descending will push the smallest item to the bottom of the array, then
    // the next smallesnt next to it, and so forth until it's sorted with the
    // largest at the top.
    switch (bubblesort_get_sort_direction()) {
      case 'ascending':
        if ($form_state['array'][$j + 1] < $form_state['array'][$j]) {
          // Swapping array values in a single line without creating a new
          // variable.
          list($form_state['array'][$j], $form_state['array'][$j + 1]) = array($form_state['array'][$j + 1], $form_state['array'][$j]);
        }
        break;

      case 'descending':
      default:
        if ($form_state['array'][$j + 1] > $form_state['array'][$j]) {
          // Swapping array values in a single line without creating a new
          // variable.
          list($form_state['array'][$j], $form_state['array'][$j + 1]) = array($form_state['array'][$j + 1], $form_state['array'][$j]);
        }
        break;
    }

    // Store the outer for loop index so we can pick where we left off.
    $form_state['i'] = $i;
    // Increment the internal for loop index and store it so we can pick up
    // where we left off.
    $form_state['j'] = ++$j;
  }

}
