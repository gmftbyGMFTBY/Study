# Introduction

---

1. GAN is for the condition Generation

   Input are controlled, need to output the corresponding project

2. generator, discriminator

   discriminator judge the item produced by the generator and output the scalar for item produced by Generator, the higher score means the discriminator think the item is real (sample from dataset, not generator).

3. Algorithm

   * Init G and D

   * In each training iteration

     1. Fix G, update D, use the data from G and dataset
     2. Fix D, update G, use the data from G

   * Optimization
     $$
     V=\frac{1}{m}\sum_{i=1}^m\log D(x) + \frac{1}{m}\sum_{i=1}^m\log (1-D(x'))\\
     \theta_d \leftarrow \theta_d + \eta \nabla V(\theta_d)\\
     V=\frac{1}{m}\sum_{i=1}^m\log (D(G(z)))\\
     \theta_g \leftarrow \theta_g - \eta \nabla V(\theta_g) 
     $$

4. Structured Learning

   1. structured data: image, video, sentence

   2. GAN is a great structured learning method for planing generation (a big picture globally)

   3. traditional method for structured learning is `bottom up` and `top down`, but GAN is the combination of this two method

   4. why we need discriminator

      Another Generation model is `Auto-Encoder`, but the Generalization performance of the `Auto-Encoder` is bad, and `VAE` can solve this problem.

      VAE try to use MSE to make the `generation data` and `input data` closely, but use MSE to decide is a bad idea (specially from the human perspective), because in the structured learning, the relationship among the components is important.

      So, we can get a easy formula that GAN = VAE + MLP(Deep), VAE must use the deep structured to model the relationship among the components.

   5. Can discriminator generate the data ?

      The only way to achieve this idea is to iterations all the data and choose the best as the output of discriminator.

      sometimes, we also need the negative data to train the discriminator.

      So, in order to reduce the complexity of the discriminator, so use the generator to low the score of the data which is not like the real data.

5. Pros and Cons

   * Generator: 
     * Pros: easy to generate
     * Cons: hard to learn the component relationship
   * Discriminator:
     * Pros: have the big picture
     * Cons: Hard to generator

   The loss of generator is leaded by the discriminator.

6. Compare with VAE

   * VAE is stable
   * GAN may be better

---

# Condition GAN

---

1. Condition GAN can control the output with the input vector
2. Example for Text-to-Image, the tradition way show the average performance of the dataset.
3. ​