/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var Yoga = Yoga || require("../../sources/entry-" + process.env.TEST_ENTRY);

it("dont_measure_single_grow_shrink_child", function () {
  (function () {
    var allocated = [];

    var root = new Yoga.Node();
    root.setWidth(100);
    root.setHeight(100);

    var measureCounter = getMeasureCounter(null, 100, 100);

    var root_child0 = new Yoga.Node();
    allocated.push(root_child0);
    root_child0.setMeasureFunc(measureCounter.inc);
    root_child0.setFlexGrow(1);
    root_child0.setFlexShrink(1);
    root.insertChild(root_child0, 0);
    root.calculateLayout(Yoga.UNDEFINED, Yoga.UNDEFINED, Yoga.DIRECTION_LTR);

    console.assert(0 === measureCounter.get(), "0 === measureCounter.get() (" + measureCounter.get() + ")");

    if (typeof root !== "undefined")
      root.freeRecursive();

    for (var t = 0; t < allocated.length; ++t) {
      allocated[t].release();
    }
  }());

  (typeof gc !== "undefined") && gc();
  console.assert(0 === Yoga.getInstanceCount(), "0 === Yoga.getInstanceCount() (" + Yoga.getInstanceCount() + ")");
});
