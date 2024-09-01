#pragma once

namespace ThanksEngine::Graphics
{
	class Texture
	{
	public:
		static void UnbindPS(uint32_t slot);

		enum class Format
		{
			RGBA_U8,
			RGBA_U32
		};

		Texture() = default;
		virtual ~Texture();

		// delete copy
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		// allow move
		Texture(Texture&&) noexcept;
		Texture& operator=(Texture&&) noexcept;

		virtual void Initialize(const std::filesystem::path& fileName);
		virtual void Terminate();

		void BindVS(uint32_t slot) const;
		void BindPS(uint32_t slot) const;

		void* GetRawData() const;

	private:
		ID3D11ShaderResourceView* mShaderResourceView = nullptr;
	};
}