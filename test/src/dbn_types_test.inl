//=======================================================================
// Copyright (c) 2014-2016 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

// Layer <- std::vector<float>
TEMPLATE_TEST_CASE_4(TYPES_TEST_PREFIX "/types/1", "[unit][types]", DBN, TYPES_TEST_T1, TYPES_TEST_T2, TYPES_TEST_T3, TYPES_TEST_T4) {
    auto dataset = mnist::read_dataset_direct<std::vector, std::vector<float>>(200);
    mnist::binarize_dataset(dataset);

    typename DBN::dbn_t dbn_fake;
    DBN::init(dbn_fake);

    dbn_fake.pretrain_denoising(dataset.training_images, dataset.training_images, 10);

    typename DBN::dbn_t dbn;
    DBN::init(dbn);

    auto& sample = dataset.training_images[1];

    dbn.pretrain(dataset.training_images, 10);
    REQUIRE(dbn.fine_tune(dataset.training_images, dataset.training_labels, 50) < 0.9);

    auto fa = dbn.features(sample);
    auto fc = dbn.activation_probabilities(sample);
    auto fd = dbn.train_activation_probabilities(sample);
    auto fe = dbn.test_activation_probabilities(sample);
    auto ff = dbn.full_activation_probabilities(sample);

    REQUIRE(dbn.predict(sample) < 10);
    REQUIRE(dbn.predict_label(fa) < 10);
    REQUIRE(dbn.predict_label(fc) < 10);
    REQUIRE(dbn.predict_label(fd) < 10);
    REQUIRE(dbn.predict_label(fe) < 10);
    cpp_unused(ff);
}
